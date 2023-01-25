/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 11:30:51 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/17 17:33:13 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It reallocates memory.
 * 
 * @param ptr The pointer to the memory block to be reallocated.
 * @param size The size of the memory block, in bytes.
 * 
 * @return A pointer to a string.
 */
void	*ft_realloc(void *ptr, size_t size)
{
	char	*tmp;

	if (ptr && size)
	{
		tmp = ft_memalloc(size);
		ft_strcpy(tmp, ptr);
		ft_strdel(((void *)&ptr));
		return (tmp);
	}
	return (NULL);
}
