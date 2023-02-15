/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:05:23 by mbarutel          #+#    #+#             */
/*   Updated: 2021/11/16 14:05:23 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * > This function takes a pointer to a memory area, a character to fill it 
 * with, and a size, and fills the memory area with the character
 * 
 * @param b This is the pointer to the memory area to be filled.
 * @param c The character to fill the memory with.
 * @param len the number of bytes to fill
 * 
 * @return The address of the first byte of the memory area b.
 */
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
	{
		((char *)b)[i] = c;
		i++;
	}
	return (b);
}
