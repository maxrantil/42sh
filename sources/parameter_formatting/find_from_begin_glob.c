/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_from_begin_glob.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:36:24 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 13:24:42 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*find_from_begin_glob(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i] == needle[j])
		{
			i++;
			j++;
			if (!haystack[i])
			{
				return (haystack);
			}
			if (!needle[j])
			{
				//ft_printf(" haystack [%s] \n", &haystack[i]);
				return (&haystack[i]);
			}
		}
		i++;
	}
	return (haystack);
}
