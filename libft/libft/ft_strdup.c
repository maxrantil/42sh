/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:08:13 by mbarutel          #+#    #+#             */
/*   Updated: 2021/11/16 14:08:13 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It duplicates a string.
 * 
 * @param s1 The string to be copied.
 * 
 * @return A pointer to a new string.
 */
char	*ft_strdup(const char *s1)
{
	char	*ret;

	ret = (char *)ft_memalloc(ft_strlen(s1) + 1);
	if (ret)
	{
		ret = ft_strcpy(ret, s1);
		return (ret);
	}
	return (NULL);
}
