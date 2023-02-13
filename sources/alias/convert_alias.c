/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:59:28 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/13 20:26:52 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	check_command_separator(char *line)
{
	char	*first_word;
	int		ret;

	first_word = get_first_word(line);
	if ((ft_strequ(first_word, "&&") == 1)
		|| (ft_strequ(first_word, "||") == 1)
		|| (ft_strequ(first_word, "&") == 1)
		|| (ft_strequ(first_word, "|") == 1)
		|| (ft_strequ(first_word, ";") == 1)
	)
	{
		ret = 1;
	}
	else
		ret = 0;
	ft_strdel(&first_word);
	return (ret);
}

//	converts only first word if found. rm converted tmp-alias to prevent loops
void	convert_first_word(char ***alias, char **line, int size)
{
	int		pos;
	char	*content;
	char	*post_content;
	char	*command;

	content = NULL;
	post_content = NULL;
	// ft_printf(" x line (%s)\n", *line);
	// ft_printf("A\n");
	pos = match_first_word(*alias, *line);
	// ft_printf("A1\n");
	while (pos != -1 && size > 0)
	{
	// ft_printf("B\n");
		content = get_alias_content_no_quotes((*alias)[pos]);
	// ft_printf("C\n");
		command = get_alias_command((*alias)[pos]);
	// ft_printf("D\n");
		post_content = get_post_content(*line, command);
	// ft_printf("E\n");
		ft_strdel(line);
		*line = ft_strjoin(content, post_content);
	// ft_printf("F\n");
		remove_alias_single(alias, pos, size--);
		ft_strdel(&command);
		ft_strdel(&post_content);
		ft_strdel(&content);
		pos = match_first_word(*alias, *line);
	}
	// ft_printf("END\n");
}

char	*check_valid_input(char *line, int i)
{
	char	*arg;

	if (!line)
		return (NULL);
	if (!(line[i]) || line[i] == '\\')
		return (NULL);
	// ft_printf("(%s)\n", &(line[i]));
	// ft_printf("(%s)\n", line);
	// if (line)
	// 	exit(0);
	arg = get_first_word(&(line[i]));
	if (arg[0] == '\'' || arg[0] == '\"')
	{
		ft_strdel(&arg);
		return (NULL);
	}
	return (arg);
}

int	convert_alias(char ***dup_alias, char **line, int i)
{
	int		pos;
	char	*arg;
	char	*content;
	char	*post_content;

	arg = check_valid_input(*line, i);
	if (!arg)
		return (0);
	pos = check_alias_match(*dup_alias, arg);
	if (pos != -1)
	{
		// ft_printf("ARG (%s)\nLINE (%s)\n", arg, *line);
		content = get_alias_content_no_quotes((*dup_alias)[pos]);
		post_content = get_post_content((*line), arg);
		ft_strdel(&arg);
		arg = ft_strjoin(content, post_content);

		// remove_alias_single(dup_alias, pos, ft_strarray_size(*dup_alias));

		conversion_dispatch(dup_alias, &arg, &content, pos);
		ft_strdel(line);
		*line = ft_strdup(arg);
		ft_strdel(&post_content);
		ft_strdel(&arg);
		return (1);
	}
	ft_strdel(&arg);
	return (0);
}

size_t  total_line_len(char *pre, char *convert, char *post, char **new_line)
{
    size_t  tot_len;

    tot_len = 0;
    if (pre)
        tot_len += ft_strlen(pre);
    if (convert)
        tot_len += ft_strlen(convert);
    if (post)
        tot_len += ft_strlen(post);
    if (tot_len > 0)
        *new_line = ft_strnew(tot_len);
    return (tot_len);
}

void    free_parsed_alias_line(char **pre, char **conv, char **post, char **new_line)
{
    if (pre && *pre)
        ft_strdel(pre);
	// ft_printf("a\n");
    if (conv && *conv)
        ft_strdel(conv);
	// ft_printf("b\n");
    if (post && *post)
        ft_strdel(post);
	// ft_printf("c\n");
    if (new_line && *new_line)
        ft_strdel(new_line);
	// ft_printf("d\n");
}

void    connect_alias_pieces(char **pre, char **convert, char **post, char **line)
{
    char    *new_line;

    if (total_line_len(*pre, *convert, *post, &new_line))
    {
        ft_strdel(line);
        if (*pre)
        {
            ft_strcpy(new_line, *pre);
            if (*convert)
                ft_strcat(new_line, *convert);
            if (*post)
                ft_strcat(new_line, *post);
        }
        else if (*convert)
        {
            ft_strcpy(new_line, *convert);
            if (*post)
                ft_strcat(new_line, *post);
        }
        else
            ft_strcpy(new_line, *post);
        *line = ft_strdup(new_line);
        free_parsed_alias_line(pre, convert, post, &new_line);
    }
}

int	skip_to_next_word_separator(char *line)
{
	int	i;

	i = 1;
	if (!line[i])
		return (i);
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	if (line[i])
		return (i);
	else
		return (i - 1);
}

void	check_line_separators(char ***alias, char **line)
{
	int		i;
	char	*pre_semicolon;
	char	*conversion;

	i = 0;
	pre_semicolon = NULL;
	conversion = NULL;
	// ft_printf("--line (%s)\n", *line);
	while ((*line)[i])
	{
		if (is_command_separator((*line)[i]))
		{
			while ((*line)[i] && is_command_separator((*line)[i]))
				i++;
			if (!(*line)[i])
				return ;
			if (i > 0)
				pre_semicolon = ft_strsub(*line, 0, i + 1);

			conversion = ft_strsub(*line, i, ft_strlen(&(*line)[i]));

			// ft_printf("i (%d)\n", i);
			// conversion = ft_strsub(*line, i, ft_strlen(&(*line)[i]));
			// ft_printf("- 1 line (%s) i (%d)\n", *line, i);
			// i += skip_to_next_word_separator(&(*line)[i]);		// working??
			// ft_printf("- 2 line (%s) i (%d)\n", *line, i);
	// pre_semicolon = save_pre_semicolon(*line, i);
			// ft_printf("- 3 pre (%s)\n", pre_semicolon);

			// echo inf ;j
			// echo inf ;0

			ft_printf("conv (%s) - pre (%s)\n", conversion, pre_semicolon);

			if (convert_alias(alias, &conversion, 0))	// conv happening
			{
				ft_strdel(line);
				*line = ft_strjoin_three(pre_semicolon, "", conversion);
				i--;
			}
			else	// conv not found. move on
			{
				if (pre_semicolon)
					ft_strdel(&pre_semicolon);
				ft_strdel(&conversion);
			}
			// 	ft_strdel(&pre_semicolon);

			// if (!validate_whitespace(conversion))
			// {
			// 	// line = pre;
			// 	return ;
			// }
			/*
							  012345678901	(len 12)
				start line = (echo inf ; j)
				i = 9

				pre = ([echo inf ;] j) ->	ft_strsub(*line, 0, i + 1)
			*/
	// if (convert_alias(alias, line, i))
	// 	update_alias_line(line, &pre_semicolon);
	// else
	// 	ft_strdel(&pre_semicolon);

			// ft_strdel(&conversion);
			// ft_printf("----line (%s) i (%d)\n", *line, i);
			// exit(1);
			// i--;			//
		}
		i++;
		// if (i > 220)			// INF LOOP
		// {
		// 	ft_printf("220 EXIT\n");
		// 	exit (1);
		// }
	}
	// exit(12);
}


void	alias_convert_line(char **line, t_shell *sh)
{
	char	**dup_alias;
	char	*post;
	char	*conversion;
	char	*pre;
	int		i;
	int		j;

    if (!validate_whitespace(*line))
      return ;
	dup_alias = ft_dup_doublearray(sh->alias);
	i = ft_strlen(*line) - 1;
	pre = NULL;
	post = NULL;
	conversion = NULL;

	// ft_printf("line (%s)\n", *line);
	/*
		01234567890123		 012 3 45678 9 012 3
		a b; a b ;a b;		 a b ;  a b  ; a b ;
        pre     conv    post
        r1 i = 13, j = 9, pre = 0-9 (10), convert =  10-13 (4), post = -        OK      OK      OK
        r2 i = 9, j = 3, pre = 0-3 (4), convert = 4-9 (6), post = 10-13 (4)     OK      OK      OK
        r1 i = 3, j = -1, pre = -(), convert = 0-3 (4), post = 4-13 (10)        OK      OK      OK
	*/
	while (i >= 0)
	{
        // i = end pos, j = start pos
		// ft_printf("line 1(%s)\n", *line);
		j = i;
		while (j >= 0 && is_command_separator((*line)[j]))  // skip separator
			j--;
		while (j >= 0 && !is_command_separator((*line)[j]))    // skip until -1 or separator
			j--;
		// ft_printf("ST line (%s)\n", *line);
		// ft_printf("i = (%d) j (%d)\n", i, j);
		if ((*line)[i + 1])
			post = ft_strsub(*line, i + 1, ft_strlen(&(*line)[i + 1]));
		if (j == -1)
		{
		    conversion = ft_strsub(*line, 0, i + 1);
		}
		else
		{
		    conversion = ft_strsub(*line, j + 1, i - j);
			pre = ft_strsub(*line, 0, j + 1);
		}
		// ft_printf("START line (%s)--\n", *line);
		// print_alias_all(dup_alias, sh);
		// ft_printf("--\n");
        convert_alias(&dup_alias, &conversion, 0);
		// ft_printf("START line 2 (%s)--\n", *line);
		// ft_printf("--\n");
		// print_alias_all(dup_alias, sh);
		// ft_printf("--\n");
            // instead line checker loop, first conversion and then loop
            // func to check the line again, for the ; and next conversions (acl?)
			// void	check_line_separators(char ***alias, char **line)
		check_line_separators(&dup_alias, &conversion);
        //
		// ft_printf("pre (%s)\n", pre);
		// ft_printf("line (%s)\n", *line);
		// ft_printf("conversion (%s)\n", conversion);
		// ft_printf("post (%s)\n", post);
		connect_alias_pieces(&pre, &conversion, &post, line);
        free_and_refill_dup_alias(&dup_alias, sh->alias);
		i = j;
		ft_printf("\tLOOP line (%s)\n", *line);
	}
	ft_free_doublearray(&dup_alias);
	if (!validate_whitespace(*line))
		ft_strdel(line);

    ft_printf("\tFINAL (%s)\n", *line);
}
