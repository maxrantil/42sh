/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:20:38 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/09 12:38:30 by mbarutel         ###   ########.fr       */
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
	&& (!*end || !special_char_check(line, *end - 1, '\\'))))
	{
		if (!*quote_flag)
			*quote_flag = line[*end];
		else if (*quote_flag == line[*end])
			*quote_flag = 0;
	}
	++(*end);
}
