/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:10:57 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/07 18:12:47 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It compares the first character of the needle to the first character of the
 * haystack. If they are the same, it compares the needle to the haystack 
 * starting at the first character of the haystack. If the needle is found,
 * it returns a pointer to the first character of the needle in the haystack.
 * If the needle is not found, it returns NULL
 * 
 * @param haystack The string to search in
 * @param needle "ll"
 * 
 * @return The address of the first character of the first occurrence of the
 * string needle in the string haystack.
 */
char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;

	if (((char *)needle)[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strncmp(&haystack[i], needle, ft_strlen(needle)) == 0)
				return (&((char *)haystack)[i]);
		}
		i++;
	}
	return (NULL);
}
