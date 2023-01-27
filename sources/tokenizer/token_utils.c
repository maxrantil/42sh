/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:34:50 by jakken            #+#    #+#             */
/*   Updated: 2023/01/27 11:10:04 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	is_semi_or_amp(char c)
{
	return (c == ';' || c == '&');
}

int	is_seperator(char c)
{
	return (c == '|' || c == '>' || c == '<'
		|| c == ';' || c == '&');
}

void	tok_quote_flag(char *line, int *end, char *quote_flag)
{
	if (line[*end] == '\'' || (line[*end] == '\"' \
	&& (!*end || !ft_bslash_check(line, *end))))
	{
		if (!*quote_flag)
			*quote_flag = line[*end];
		else if (*quote_flag == line[*end])
			*quote_flag = 0;
	}
	++(*end);
}
