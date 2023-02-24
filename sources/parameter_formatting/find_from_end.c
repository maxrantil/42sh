/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_from_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:35:19 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/24 11:34:57 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*find_from_end(char *haystack, char *needle, int glob)
{
	int		len;
	int		len_needle;
	char	*temp;

	len = (int)ft_strlen(haystack);
	len_needle = (int)ft_strlen(needle);
	if ((!*needle && glob == 2) || !len_needle)
		return (ft_strnew(1));
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
				return (ft_strnew(1));
			return (temp);
		}
	}
	return (ft_strdup(haystack));
}
