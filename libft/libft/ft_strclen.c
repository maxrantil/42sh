/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:19:35 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/31 10:26:56 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strclen(char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		if (str[i] == c)
			return (i);
	}
	return (0);
}
