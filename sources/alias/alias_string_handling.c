/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_string_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:04:27 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/14 22:38:02 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	add_space(char **next)
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
			full = ft_strjoin(*line, *next);
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

static int	validate_two_input(char *mid, char *orig_post)
{
	if (!(mid) || !(orig_post))
		return (0);
	if (ft_strlen(mid) == 0 || ft_strlen(orig_post) == 0)
		return (0);
	return (1);
}

void	trim_mid_word(char **mid, char **orig_post)
{
	ssize_t	mid_len;
	ssize_t	post_len;
	char	*trimmed_mid;
	char	*post;

	if (!validate_two_input(*mid, *orig_post))
		return ;
	post = ft_strtrim(*orig_post);
	ft_strdel(orig_post);
	post_len = ft_strlen(post);
	mid_len = ft_strlen(*mid);
	while (post_len >= 0 && mid_len >= 0 && (*mid)[mid_len] == post[post_len])
	{
		post_len--;
		mid_len--;
	}
	if (mid_len > 0)
	{
		trimmed_mid = ft_strsub(*mid, 0, mid_len);
		ft_strdel(mid);
		*mid = ft_strdup(trimmed_mid);
		ft_strdel(&trimmed_mid);
	}
	*orig_post = ft_strdup(post);
	ft_strdel(&post);
}

char	*get_mid_word(char *line)
{
	int		i;
	size_t	len;

	if (word_count(line) < 2)
		return (ft_strdup(""));
	i = skip_to_second_word(line);
	if (line[i])
	{
		len = ft_strlen(&line[i]);
		return (ft_strsub(line, i, len));
	}
	else
		return (ft_strdup(""));
}
