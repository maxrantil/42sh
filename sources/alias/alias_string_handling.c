/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_string_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:04:27 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/10 21:51:34 by rvuorenl         ###   ########.fr       */
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

	// ft_printf("skip  (%s)\n", line);
	i = 1;
	if (!(line[i]))
		return (1);
	// ft_printf("skip 1(%s)\n", &(line[1]));
	while (line[i] && ft_iswhitespace(line[i])
		&& !(is_command_separator(line[i])))
		i++;
	// ft_printf("a (%d) (%s)\n", i, &(line[i]));
	while (line[i] && line[i + 1] && !(ft_iswhitespace(line[i]))
		&& !(is_command_separator(line[i])))
		i++;
	if (line[i] && is_command_separator(line[i]))
		return (i - 1);
	// ft_printf("b (%d) (%s)\n", i, &(line[i]));
	while (line[i] && ft_iswhitespace(line[i])
		&& !(is_command_separator(line[i])))
		i++;
	// ft_printf("c (%d) (%s)\n", i, &(line[i]));
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

	// ft_printf("a\n");
	add_space(next);
	// ft_printf("b\n");
	// ft_printf("b\n");
	if (next && *next)
	{
	// ft_printf("c\n");
		if (post && *post)
		{
	// ft_printf("d\n");
			full = ft_strjoin_three(*line, *next, *post);
			ft_strdel(post);
	// ft_printf("e\n");
		}
		else
		{
	// ft_printf("f\n");

			full = ft_strjoin(*line, *next);
	// ft_printf("g\n");
		}
		ft_strdel(next);
	// ft_printf("h\n");
	}
	else if (*post)
	{
	// ft_printf("i\n");
		full = ft_strjoin(*line, *post);
		ft_strdel(post);
	// ft_printf("j\n");
	}
	else
		return ;
	// ft_printf("k\n");
	ft_strdel(line);
	*line = ft_strdup(full);
	ft_strdel(&full);
	// ft_printf("l\n");
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
