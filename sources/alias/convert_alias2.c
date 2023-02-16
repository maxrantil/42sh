/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_alias2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:52:54 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/16 12:53:47 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	check_next_conversion(char **alias, int del)
{
	size_t	len;
	int		ret_value;

	ret_value = 0;
	if (!(*alias))
		return (ret_value);
	len = ft_strlen(*alias);
	if (len == 0)
		ret_value = 1;
	else if (ft_iswhitespace((*alias)[len - 1]))
		ret_value = 1;
	if (del)
		ft_strdel(alias);
	return (ret_value);
}

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

static void	free_conv_loop(char ***alias, char **content)
{
	ft_free_doublearray(alias);
	ft_strdel(content);
}

void	conversion_loop(char ***alias, char **line, char **cont, char ***dup)
{
	int		pos;
	char	*next_word;
	char	*post_content;
	char	*mid_word;

	mid_word = get_mid_word(*cont, &next_word);
	post_content = convert_first(dup, alias, line, *cont);
	trim_mid_word(&mid_word, &post_content);
	append_to_converted(line, &mid_word, &next_word);
	while (*cont && (check_next_conversion(cont, 1)))
	{
		get_first_word_move_post(&post_content, &next_word, line);
		pos = match_first_word(*dup, next_word);
		if (pos != -1)
		{
			*cont = get_alias_content_no_quotes((*dup)[pos]);
			mid_word = convert_first(dup, alias, &next_word, next_word);
			append_to_converted(line, &next_word, &mid_word);
		}
		else
			break ;
		free_and_refill_dup_alias(dup, *alias);
	}
	append_to_converted(line, &next_word, &post_content);
	free_conv_loop(dup, cont);
}
