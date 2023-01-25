/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrclean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:19:47 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/28 08:54:41 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * This function frees the memory allocated to a 2D array of strings
 * 
 * @param array The array to be cleaned.
 */
void	ft_arrclean(char **array)
{
	int	i;

	i = -1;
	while (*(array + (++i)))
		ft_strdel(array + i);
	ft_memdel((void **)&array);
}
