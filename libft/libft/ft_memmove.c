/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:05:13 by mbarutel          #+#    #+#             */
/*   Updated: 2021/11/16 14:05:13 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It copies the memory area pointed to by src to the memory area pointed to
 * by dst.
 * 
 * @param dst pointer to the destination array where the content is to be 
 * copied, type-casted to a pointer of type void *.
 * @param src pointer to the source array
 * @param len the number of bytes to copy
 * 
 * @return The pointer to the destination string.
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		while (i++ < len)
			((char *)dst)[len - i] = ((char *)src)[len - i];
	}
	else
	{
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}	
	}
	return (dst);
}
