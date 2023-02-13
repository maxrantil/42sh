/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_from_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:35:19 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/11 11:20:24 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*find_from_end(char *haystack, char *needle)
{
	int	len;
	int	len_needle;

	len = (int)ft_strlen(haystack);
	//ft_printf("haystack %s len [%d]]\n",haystack, len);
	while (len > 0)
	{
		len_needle = (int)ft_strlen(needle);
		while (haystack[len] == needle[len_needle])
		{
			len--;
			len_needle--;
			if (len == 0)
			{
				return (NULL);
			}
			if (len_needle == 0)
			{
				//ft_printf(" haystack [%s] \n", &haystack[len]);
				haystack = ft_strndup(haystack, ft_strlen(haystack) - ft_strlen(needle) + 1);
				return (haystack);
			}
		}
		len--;
	}
	return (haystack);
}
