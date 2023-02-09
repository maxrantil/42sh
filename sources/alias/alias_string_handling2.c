/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_string_handling2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:11:04 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/09 11:17:52 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	get_first_word_move_post(char **post_content, char **next_word)
{
	char	*new_post;

	if (*next_word)
		ft_strdel(next_word);
	if (!(*post_content))
		return ;
	*next_word = get_first_word(*post_content);
	new_post = get_post_content(*post_content, *next_word);
	ft_strdel(post_content);
	*post_content = ft_strdup(new_post);
	ft_strdel(&new_post);
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

void	trim_mid_word(char **mid, char **orig_post)
{
	ssize_t	mid_len;
	ssize_t	post_len;
	char	*trimmed_mid;
	char	*post;

	if (!(*mid) || !(*orig_post))
		return ;
	if (ft_strlen(*mid) == 0 || ft_strlen(*orig_post) == 0)
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

char	*save_pre_semicolon(char *line, int pos)
{
	if (pos > 0)
		return (ft_strsub(line, 0, pos));
	else
		return (ft_strdup(""));
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
