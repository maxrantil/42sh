/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_from_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:35:19 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/22 22:29:09 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*find_from_end(char *haystack, char *needle, int glob)
{
	int		len;
	int		len_needle;
	char	*temp;

	len = (int)ft_strlen(haystack) - 1;
	len_needle = (int)ft_strlen(needle) - 1;

	while (haystack[len] == needle[len_needle])
	{
		len--;
		len_needle--;
		if (len < 0 && len_needle > 0)
			return (ft_strdup(haystack));
		if (len_needle < 0)
		{
			temp = ft_strndup(haystack, \
			ft_strlen(haystack) - ft_strlen(needle));
			if (glob == 2)
				return (NULL);
			return (temp);
		}
	}
	return (ft_strdup(haystack));
}
