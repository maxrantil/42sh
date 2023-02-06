/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_if_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:21:17 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/26 09:55:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*tok_if_logical(char *line, int *i, int *start, int *end)
{
	if ((line[*i] == '|' && line[*i + 1] == '|')
		|| (line[*i] == '&' && line[*i + 1] == '&'))
	{
		*start = *i;
		*end = *start + 2;
		if (test_if_error(&line[*end - 1]))
		{
			*end = -1;
			return (NULL);
		}
		return (ft_strsub(line, *start, 2));
	}
	else if (line[*i] == '&')
	{
		*start = *i;
		*end = *start + 1;
		if (test_if_error(&line[*end - 1]))
		{
			*end = -1;
			return (NULL);
		}
		return (ft_strsub(line, *start, 1));
	}
	return (NULL);
}
