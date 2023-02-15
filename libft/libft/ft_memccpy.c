/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:04:29 by mbarutel          #+#    #+#             */
/*   Updated: 2021/11/16 14:04:29 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copy bytes from src to dst until c is found, or n bytes have been copied,
 * whichever comes first
 * 
 * @param dst pointer to the destination array where the content is to be copied,
 * type-casted to a pointer of type void*.
 * @param src The source string.
 * @param c the character to stop copying at
 * @param n the number of bytes to copy
 * 
 * @return The address of the next byte after the first occurrence of c in the
 * string src.
 */

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = -1;
	if (!dst && !src)
		return (NULL);
	while (++i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		if (((unsigned char *)src)[i] == (unsigned char)c)
			return (&((unsigned char *)dst)[i + 1]);
	}
	return (NULL);
}
