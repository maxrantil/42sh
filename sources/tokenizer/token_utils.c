/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 21:20:38 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/15 13:39:14 by mviinika         ###   ########.fr       */
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

void	tok_quote_flag(char *line, int *end, t_token_flags *flags)
{
	if (line[*end] == S_QUO || (line[*end] == D_QUO \
	&& (!*end || !special_char_check(line, *end, '\\'))))
	{
		if (!flags->quote)
			flags->quote = line[*end];
		else if (flags->quote == line[*end])
			flags->quote = 0;
	}
	else if ((line[*end] == L_BRAC \
	&& (!*end || special_char_check(line, *end, '$'))) || line[*end] == R_BRAC)
	{
		if ((!flags->braces || flags->braces == line[*end]) && line[*end] == L_BRAC)
		{
			flags->braces = line[*end];
			++flags->braces_count;
		}
		else if (flags->braces != line[*end])
		{
			--flags->braces_count;
			if (!flags->braces_count)
				flags->braces = 0;
		}
	}
	++(*end);
}
