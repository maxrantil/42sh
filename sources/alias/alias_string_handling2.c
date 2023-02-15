/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_string_handling2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:11:04 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/15 11:42:24 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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

void	remove_quotes_cmd(char *cmd)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(cmd);
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			ft_memmove(&cmd[i], &cmd[i + 1], len - i);
			len--;
		}
		else
			i++;
	}
}

static	int	skip_space_separators(int *i, int *j, char **post, char **next)
{
	if (*next)
		ft_strdel(next);
	if (!(*post))
		return (1);
	(*i) = 0;
	(*j) = 0;
	while ((*post)[(*i)] && ft_iswhitespace((*post)[(*i)]))
		(*i)++;
	while ((*post)[(*i) + (*j)] && is_command_separator((*post)[(*i) + (*j)]))
		(*j)++;
	return (0);
}

static void	update_first_post(char **next, char **post, char **new_post)
{
	*next = get_first_word(*post);
	*new_post = get_post_content(*post, *next);
}

void	get_first_word_move_post(char **post, char **next, char **line)
{
	char	*new_post;
	char	*separator;
	int		i;
	int		j;

	if (skip_space_separators(&i, &j, post, next))
		return ;
	if (j > 0)
	{
		separator = ft_strsub(*post, 0, i + j);
		j = 0;
		while (separator[j] && ft_iswhitespace(separator[j]))
		{
			ft_memmove(&(separator)[0], &(separator)[1], ft_strlen(separator));
			j = 0;
		}
		new_post = get_post_content(*post, separator);
		append_to_converted(line, &separator, NULL);
		*next = ft_strdup("");
	}
	else
		update_first_post(next, post, &new_post);
	ft_strdel(post);
	*post = ft_strdup(new_post);
	ft_strdel(&new_post);
}
