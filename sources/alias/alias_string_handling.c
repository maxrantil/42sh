/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_string_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:04:27 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/13 20:35:22 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	add_quotes(char **content)
{
	char	*added_quotes;
	char	*tmp;
	int		i;

	i = 0;
	tmp = *content;
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
		{
			strip_quotes_single(tmp, i);
		}
		i++;
	}
	added_quotes = ft_strjoin_three("\'", tmp, "\'");
	ft_strdel(content);
	*content = ft_strdup(added_quotes);
	ft_strdel(&added_quotes);
}

int	skip_to_second_word(char *line)
{
	int	i;

	i = 1;
	if (!(line[i]))
		return (1);
	while (line[i] && ft_iswhitespace(line[i])
		&& !(is_command_separator(line[i])))
		i++;
	while (line[i] && line[i + 1] && !(ft_iswhitespace(line[i]))
		&& !(is_command_separator(line[i])))
		i++;
	if (line[i] && is_command_separator(line[i]))
		return (i - 1);
	while (line[i] && ft_iswhitespace(line[i])
		&& !(is_command_separator(line[i])))
		i++;
	return (i);
}

void	add_space(char **next)
{
	char	*new;

	if (*next)
	{
		new = ft_strjoin(" ", *next);
		ft_strdel(next);
		*next = ft_strdup(new);
		ft_strdel(&new);
	}
}

void	append_to_converted(char **line, char **next, char **post)
{
	char	*full;

	add_space(next);
	if (next && *next)
	{
		if (post && *post)
		{
			full = ft_strjoin_three(*line, *next, *post);
			ft_strdel(post);
		}
		else
		{
			full = ft_strjoin(*line, *next);
		}
		ft_strdel(next);
	}
	else if (*post)
	{
		full = ft_strjoin(*line, *post);
		ft_strdel(post);
	}
	else
		return ;
	ft_strdel(line);
	*line = ft_strdup(full);
	ft_strdel(&full);
}

void	append_next_word(char **line, char **next)
{
	char	*full;

	if (*next)
	{
		full = ft_strjoin_three(*line, " ", *next);
		ft_strdel(line);
		ft_strdel(next);
		*line = ft_strdup(full);
		ft_strdel(&full);
	}
}
