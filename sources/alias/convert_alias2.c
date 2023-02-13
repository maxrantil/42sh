/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_alias2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:52:54 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/13 20:33:39 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	check_next_conversion(char *alias)
{
	size_t	len;

	if (!alias)
		return (0);
	len = ft_strlen(alias);
	if (len == 0)
		return (1);
	else if (ft_iswhitespace(alias[len - 1]))
		return (1);
	return (0);
}

void	update_alias_line(char **line, char **pre_semicolon)
{
	char	*full;

	full = ft_strjoin_three(*pre_semicolon, " ", *line);
	ft_strdel(line);
	ft_strdel(pre_semicolon);
	*line = ft_strdup(full);
	ft_strdel(&full);
}

//	convert first of line to final-form, return rest of the line
char	*convert_first(char ***dup, char ***alias, char **line, char *cont)
{
	char	*first_word;
	char	*post_content;

	if (!*dup)
		*dup = ft_dup_doublearray(*alias);
	first_word = get_first_word(*line);
	post_content = get_post_content(*line, cont);
	convert_first_word(dup, &first_word, ft_strarray_size(*dup));
	if (first_word && ft_strlen(first_word) > 0)
	{
		ft_strdel(line);
		*line = ft_strdup(first_word);
		ft_strdel(&first_word);
	}
	if (first_word)
		ft_strdel(&first_word);
	free_and_refill_dup_alias(dup, *alias);
	return (post_content);
}

void	conversion_loop(char ***alias, char **line, char **content)
{
	int		pos;
	char	**dup_alias;
	char	*next_word;
	char	*post_content;
	char	*mid_word;

	dup_alias = NULL;
	mid_word = get_mid_word(*content);
	post_content = convert_first(&dup_alias, alias, line, *content);
	trim_mid_word(&mid_word, &post_content);
	next_word = NULL;
	append_to_converted(line, &mid_word, &next_word);
	while (*content && (check_next_conversion(*content)))
	{
		ft_strdel(content);
		get_first_word_move_post(&post_content, &next_word, line);
		pos = match_first_word(dup_alias, next_word);
		if (pos != -1)
		{
			*content = get_alias_content_no_quotes((dup_alias)[pos]);
			mid_word = convert_first(&dup_alias, alias, &next_word, next_word);
			append_to_converted(line, &next_word, &mid_word);
		}
		else
		{
			append_to_converted(line, &next_word, &post_content);
			break ;
		}
		free_and_refill_dup_alias(&dup_alias, *alias);
	}
	append_to_converted(line, &next_word, &post_content);
	ft_strdel(content);
}

void	conversion_dispatch(char ***alias, char **line, char **content, int pos)
{
	if (check_next_conversion(*content))
	{
		conversion_loop(alias, line, content);
	}
	else
	{
		remove_alias_single(alias, pos, ft_strarray_size(*alias));
        convert_first_word(alias, line, ft_strarray_size(*alias));
        ft_strdel(content);
	}
}
