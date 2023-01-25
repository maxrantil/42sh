/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:09:52 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/05 12:35:42 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copy at most len characters from src into dst. If src is less than len
 * characters long, the remainder of dst is filled with `\0' characters. 
 * Otherwise, dst is not terminated
 * 
 * @param dst This is the destination string.
 * @param src The string to be copied.
 * @param len the maximum number of characters to copy
 * 
 * @return The pointer to the destination string dst.
 */
char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
