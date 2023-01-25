/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:26:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 15:15:43 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:40:06 by jniemine          #+#    #+#             */
/*   Updated: 2022/10/04 18:42:44 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It allocates a new string, copies the first n characters of str into it, and
 * returns a pointer to it.
 * 
 * @param str The string to be copied.
 * @param n the number of characters to copy
 * 
 * @return A pointer to a new string.
 */
char	*ft_strndup(char *str, size_t n)
{
	char	*res;

	res = ft_memalloc(n + 1);
	if (!res)
		return (NULL);
	ft_strncpy(res, str, n);
	res[n] = '\0';
	return (res);
}
