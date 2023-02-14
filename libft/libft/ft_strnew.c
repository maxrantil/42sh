/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:10:08 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/05 12:35:49 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It creates a new string of size size + 1 and fills it with zeros.
 * 
 * @param size The size of the string to be allocated.
 * 
 * @return A pointer to a new string of size + 1.
 */
char	*ft_strnew(size_t size)
{
	char	*ret;

	ret = (char *)ft_memalloc(sizeof(char) * (size + 1));
	if (ret)
	{
		ft_bzero(ret, size + 1);
		return (ret);
	}
	return (NULL);
}
