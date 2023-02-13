/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:59:28 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/13 20:32:49 by rvuorenl         ###   ########.fr       */
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
	pos = match_first_word(*alias, *line);
	while (pos != -1 && size > 0)
	{
		content = get_alias_content_no_quotes((*alias)[pos]);
		command = get_alias_command((*alias)[pos]);
		post_content = get_post_content(*line, command);
		ft_strdel(line);
		*line = ft_strjoin(content, post_content);
		remove_alias_single(alias, pos, size--);
		ft_strdel(&command);
		ft_strdel(&post_content);
		ft_strdel(&content);
		pos = match_first_word(*alias, *line);
	}
}

char	*check_valid_input(char *line, int i)
{
	char	*arg;

	if (!line)
		return (NULL);
	if (!(line[i]) || line[i] == '\\')
		return (NULL);
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
		content = get_alias_content_no_quotes((*dup_alias)[pos]);
		post_content = get_post_content((*line), arg);
		ft_strdel(&arg);
		arg = ft_strjoin(content, post_content);
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
    if (conv && *conv)
        ft_strdel(conv);
    if (post && *post)
        ft_strdel(post);
    if (new_line && *new_line)
        ft_strdel(new_line);
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

			if (convert_alias(alias, &conversion, 0))
			{
				ft_strdel(line);
				*line = ft_strjoin_three(pre_semicolon, "", conversion);
				i--;
			}
			else
			{
				if (pre_semicolon)
					ft_strdel(&pre_semicolon);
				ft_strdel(&conversion);
			}
		}
		i++;
	}
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
	while (i >= 0)
	{
		j = i;
		while (j >= 0 && is_command_separator((*line)[j]))  // skip separator
			j--;
		while (j >= 0 && !is_command_separator((*line)[j]))    // skip until -1 or separator
			j--;
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
        convert_alias(&dup_alias, &conversion, 0);
		check_line_separators(&dup_alias, &conversion);
		connect_alias_pieces(&pre, &conversion, &post, line);
        free_and_refill_dup_alias(&dup_alias, sh->alias);
		i = j;
	}
	ft_free_doublearray(&dup_alias);
	if (!validate_whitespace(*line))
		ft_strdel(line);
    // ft_printf("\tFINAL (%s)\n", *line);
}
