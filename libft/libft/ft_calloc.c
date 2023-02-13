/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:17:08 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/07 13:22:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It allocates memory and zeroes it out.
 * 
 * @param count number of elements
 * @param size The size of the memory block, in bytes.
 * 
 * @return A pointer to the allocated memory.
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = (void *)malloc(count * size);
	if (ret)
	{
		ft_bzero(ret, (count * size));
		return (ret);
	}
	else
		ft_exit_no_mem(1);
	return (NULL);
}
