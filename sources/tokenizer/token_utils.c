/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:20:38 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/09 20:37:37 by mbarutel         ###   ########.fr       */
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

void	tok_quote_flag(char *line, int *end, char *quote, char *braces)
{
	if (line[*end] == '\'' || (line[*end] == '\"' \
	&& (!*end || !special_char_check(line, *end - 1, '\\'))))
	{
		if (!*quote)
			*quote = line[*end];
		else if (*quote == line[*end])
			*quote = 0;
	}
	else if (line[*end] == L_BRAC || (line[*end] == R_BRAC \
	&& (!*end || !special_char_check(line, *end - 1, '$'))))
	{
		if (!*braces)
			*braces = line[*end];
		else if (*braces == line[*end])
			*braces = 0;
	}
	++(*end);
}
