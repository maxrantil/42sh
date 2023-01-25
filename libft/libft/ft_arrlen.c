/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:52:56 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/22 19:42:09 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * This function returns the length of an array of strings
 * 
 * @param array The array to get the length of.
 * 
 * @return The length of the array.
 */
size_t	ft_arrlen(char **array)
{
	size_t	len;

	len = 0;
	if (array)
	{
		while (array[len])
			len++;
	}
	return (len);
}
