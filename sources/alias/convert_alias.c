/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:59:28 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/07 16:27:12 by rvuorenl         ###   ########.fr       */
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

int	convert_alias(char **line, t_shell *sh, int i)
{
	int		pos;
	char	*arg;
	char	*content;
	char	*post_content;

	arg = check_valid_input(*line, i);
	if (!arg)
		return (0);
	pos = check_alias_match(sh->alias, arg);
	if (pos != -1)
	{
		content = get_alias_content_no_quotes(sh->alias[pos]);
		post_content = get_post_content(&(*line)[i], arg);
		ft_strdel(&arg);
		arg = ft_strjoin(content, post_content);
		conversion_dispatch(sh, &arg, &content, pos);
		ft_strdel(line);
		*line = ft_strdup(arg);
		ft_strdel(&post_content);
		ft_strdel(&arg);
		return (1);
	}
	ft_strdel(&arg);
	return (0);
}

void	alias_convert_line(char **line, t_shell *sh)
{
	int		i;
	char	*pre_semicolon;

	if (!validate_whitespace(*line))
		return ;
	convert_alias(line, sh, 0);
	i = 0;
	while ((*line)[i])
	{
		if (check_command_separator(&(*line)[i]))
		{
			i += skip_to_second_word(&(*line)[i]);
			pre_semicolon = save_pre_semicolon(*line, i);
			if (convert_alias(line, sh, i))
				update_alias_line(line, &pre_semicolon);
			else
				ft_strdel(&pre_semicolon);
		}
		i++;
	}
}
