/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:05:05 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/05 12:33:23 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * This function takes a pointer to a pointer to a void, and frees the memory
 * pointed to by the pointer to a void, and sets the pointer to a void to NULL
 * 
 * @param ap This is the address of a pointer to a memory block that needs to 
 * be freed with free(3), then set to NULL.
 */
void	ft_memdel(void **ap)
{
	if (ap)
	{
		free(*ap);
		*ap = NULL;
	}
}
