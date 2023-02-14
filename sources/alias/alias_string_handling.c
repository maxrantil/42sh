/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_string_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:04:27 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/14 16:19:19 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	have_single_quotes(char *content)
{
	size_t	len;

	if (content)
		len = ft_strlen(content);
	else
		return (0);
	if (len > 0)
	{
		if (content[0] == '\'' && content[len - 1] == '\'')
			return (1);
	}
	return (0);
}


int	skip_single_quotes(char *str, int i)
{
	while (str[i] && str[i] != '\'')
		i++;
	if (!str[i])
		return (i - 1);
	return (i);
}

void	rm_double_quotes(char *str)
{
	int		i;
	size_t	len;

	// if (str)
	// {
	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '\"')
		{
			if (!(str[i + 1]))
				ft_memmove(&str[i], &str[i + 1], 1);
			else
				ft_memmove(&str[i], &str[i + 1], len - i);
			len--;
			str[len] = '\0';
			i--;
		}
		else if (str[i] == '\'')
		{
			i = skip_single_quotes(str, i);
		}
		i++;
	}
	// }
}

void	add_quotes(char **content)
{
	char	*added_quotes;
	char	*tmp;

	if (*content)
		tmp = ft_strtrim(*content);
	else
		tmp = NULL;
	if (have_single_quotes(tmp))
	{
		ft_strdel(content);
		*content = ft_strdup(tmp);
		ft_strdel(&tmp);
		return ;
	}
	if (tmp)
	{
		rm_double_quotes(tmp);
		added_quotes = ft_strjoin_three("\'", tmp, "\'");
		ft_strdel(&tmp);
	}
	else
		added_quotes = ft_strdup("''");
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
