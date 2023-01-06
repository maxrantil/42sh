/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:36:47 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/28 10:37:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsep(char **str_ptr, const char *delim)
{
	char	*begin;
	char	*end;

	begin = *str_ptr;
	if (begin == NULL)
		return (NULL);
	end = begin + ft_strcspn(begin, delim);
	if (*end)
	{
		*end++ = '\0';
		*str_ptr = end;
	}
	else
		*str_ptr = NULL;
	return (begin);
}
