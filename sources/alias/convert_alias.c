/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:59:28 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/11 14:15:08 by rvuorenl         ###   ########.fr       */
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

int	convert_alias(char **line, t_shell *sh, int i)
{
	int		pos;
	char	*arg;
	char	*content;
	char	*post_content;

	arg = check_valid_input(*line, i);
	if (!arg)
		return (0);
	// ft_printf("--arg (%s)\n", arg);
	// print_alias_all(sh->alias, sh);
	// ft_printf("--line (%s)\n", *line);
	pos = check_alias_match(sh->alias, arg);
	if (pos != -1)
	{
		// ft_printf("--pos (%d)\n", pos);
		// ft_printf("--pos (%s)\n", sh->alias[pos]);
		content = get_alias_content_no_quotes(sh->alias[pos]);
		post_content = get_post_content(&(*line)[i], arg);
		// ft_printf("\t CONV--- post (%s)\n", post_content);
		ft_strdel(&arg);
		arg = ft_strjoin(content, post_content);
		conversion_dispatch(sh, &arg, &content, pos);
		ft_strdel(line);
		*line = ft_strdup(arg);
		ft_strdel(&post_content);
		ft_strdel(&arg);
		return (1);
	}
	// ft_printf("2\n");
	// if (*line)
	// 	exit(0);
	ft_strdel(&arg);
	return (0);
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

void	alias_convert_line(char **line, t_shell *sh)
{
	int		i;
	char	*pre_semicolon;

	// ft_printf("start \n");
	// sleep(3);
	if (!validate_whitespace(*line))
		return ;

		// print_alias_all(sh->alias, sh);		// DEL


	// ft_printf("BEF (%s) (%d)\n", *line, ft_strlen(*line));
	convert_alias(line, sh, 0);
	// ft_printf("AFT (%s) (%d)\n", *line, ft_strlen(*line));
	i = 0;
	// ft_printf("mid \n");
	// sleep(2);
	while ((*line)[i])
	{
		// ft_printf("\tBEG a_c_l loop (%s) i (%d)\n", *line, i);
		// if (check_command_separator(&(*line)[i]))		// old
		if (is_command_separator((*line)[i]))
		{
			// ft_printf("\ta_c_l loop   (%s) i (%d)\n", *line, i);
			// ft_printf("\ta_c_l loop-i (%s)\n", &((*line)[i]));

			i += skip_to_next_word_separator(&(*line)[i]);
			// i += skip_to_second_word(&(*line)[i]);
			// i--;
			// ft_printf("a (%d)(%s)\n", i, *line);
			pre_semicolon = save_pre_semicolon(*line, i);
			// ft_printf("b (%d)(%s)\n", i, *line);
			// ft_printf("pre (%d)(%s)\n", i, pre_semicolon);
			if (convert_alias(line, sh, i))
				update_alias_line(line, &pre_semicolon);
			else
				ft_strdel(&pre_semicolon);
			// ft_printf("c (%d)(%s)\n", i, *line);

			// ft_printf("--- a_c_l loop (%s) i (%d)\n", *line, i);
			// ft_printf("--- a_c_l loop (%s)\n", &((*line)[i]));
			i--;
		}
		i++;
	}
	// ft_printf("\tFINAL line (%s)\n\n", *line);		// FULLY CONVERTED LINE
	// sleep(3);

	//
	// ft_strdel(line);
	// 	*line = ft_strdup("echo hello");
	//
													// LAST LINE BEFORE EXIT
}

// echo hello;k;
// 0123456789 0 1 2
// echo hello ; k ;

// echo hello;k
// 0123456789 0 1 2
// echo hello ; k
