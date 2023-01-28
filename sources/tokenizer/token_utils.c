/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/01/27 15:59:48 by mbarutel         ###   ########.fr       */
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
	&& (!*end || !special_char_check(line, *end, '\\')))) 
	{
		if (!*quote_flag)
			*quote_flag = line[*end];
		else if (*quote_flag == line[*end])
			*quote_flag = 0;
	}
	++(*end);
}
