/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_from_begin_glob.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:36:24 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/24 11:39:18 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*find_from_begin_glob(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (!*needle)
		ft_strdup(haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i] == needle[j])
		{
			i++;
			j++;
			if (!haystack[i] && needle[j])
				return (ft_strdup(haystack));
			if (!needle[j])
				return (ft_strdup(&haystack[i]));
		}
		i++;
	}
	return (ft_strdup(haystack));
}
