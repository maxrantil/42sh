/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_if_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:11:18 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/13 17:21:34 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	traverse_to_end(char *line, int *end)
{
	// ft_printf("LINE: %s\n", &line[*end]);
	while (line[*end] && ft_isspace(line[*end]))
		++(*end);
	/* Why do we need this? It is breaking in situtations like 56>&1 >&56*/
	// if (redir_error(&line[*end]))
	// {
	// 	*end = -1;
	// 	return (1);
	// }
	while (line[*end] && !ft_isspace(line[*end]) && !is_seperator(line[*end]))
		++(*end);
	while (ft_isspace(line[*end]))
		++(*end);
	return (0);
}

char	*tok_if_redir(char *line, int *i, int *start, int *end)
{
	int	digits;

	digits = 0;
	while (ft_isdigit(line[*i + digits]))
		++digits;
	if (line[*i + digits] == '>' || line[*i + digits] == '<')
	{
		*start = *i;
		*i = *i + digits;
		*end = *i + digits + 1;
		if (line[*end] == '<' || line[*end] == '>' || line[*end] == '&')
			++(*end);
		if (*end && line[(*end) - 1] == '&' && line[*end] == '-')
			return (ft_strsub(line, *start, (++(*end)) - *start));
		if (redir_error(&line[*end]))
		{
			*end = -1;
			return (NULL);
		}
		if (traverse_to_end(line, end))
			return (NULL);
		return (ft_strsub(line, *start, *end - *start));
	}
	return (NULL);
}
