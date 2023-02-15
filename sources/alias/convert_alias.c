/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:59:28 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/15 18:43:41 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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

void	trim_alias_line(char **line)
{
	char	*trimmed;

	trimmed = ft_strtrim(*line);
	ft_strdel(line);
	*line = ft_strdup(trimmed);
	ft_strdel(&trimmed);
}

static char	*check_valid_input(char *line, int i)
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

void	conversion_dispatch(char ***alias, char **line, char **cont, int pos)
{
	if (check_next_conversion(*cont))
	{
		conversion_loop(alias, line, cont);
	}
	else
	{
		remove_alias_single(alias, pos, ft_strarray_size(*alias));
		convert_first_word(alias, line, ft_strarray_size(*alias));
		ft_strdel(cont);
	}
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
