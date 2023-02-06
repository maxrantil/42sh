/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:41:30 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/26 09:55:22 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*get_file(char *value)
{
	int		start;
	int		end;
	char	*res;

	start = 1;
	if (!value)
		return (NULL);
	if (value[start] == value[start - 1] || value[start] == '&')
		++start;
	while (value[start] && ft_isspace(value[start]))
		++start;
	end = start;
	while (value[end] && !ft_isspace(value[end]))
		++end;
	if (end <= start)
		return (NULL);
	res = ft_strsub(value, start, end - start);
	return (res);
}
