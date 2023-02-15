/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:04:37 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/14 12:47:44 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The above function searches for the first occurrence of the character c 
 * (an unsigned char) in the first n bytes of the string pointed to, by the 
 * argument str.
 * 
 * @param s The string to search
 * @param c The character to search for.
 * @param n The number of bytes to be searched
 * 
 * @return The address of the first occurrence of the character c in the first 
 * n bytes of the string
 * pointed to by s.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	return (0);
}
