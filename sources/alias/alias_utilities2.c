/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utilities2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:09:56 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/08 19:13:57 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	word_count(char *line)
{
	int	i;
	int	word_count;

	word_count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_iswhitespace(line[i]))
			i++;
		if (line[i])
		{
			word_count++;
			while (line[i] && !(ft_iswhitespace(line[i])))
				i++;
			if (line[i])
				i--;
			else
				return (word_count);
		}
		else
			return (word_count);
		i++;
	}
	return (word_count);
}

ssize_t	find_matching_quote(char *str, char quote)
{
	ssize_t	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '\"'
				|| str[i + 1] == '\\' ))
			i++;
		else if (str[i] == quote)
			break ;
		i++;
	}
	return (i);
}

size_t	strip_quotes_single(char *str, size_t quote1)
{
	size_t	len;
	ssize_t	quote2;

	len = ft_strlen(str);
	quote2 = find_matching_quote(&(str[quote1]), str[quote1]);
	quote2 += quote1;
	ft_memmove(&(str[quote1]), &(str[quote1 + 1]), len - quote1);
	ft_memmove(&(str[quote2 - 1]), &(str[quote2]), len - quote2);
	return (quote2 - 2);
}
