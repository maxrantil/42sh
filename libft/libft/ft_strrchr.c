/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:10:36 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/13 12:08:15 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It returns a pointer to the last occurrence of the character c in the
 * string s.
 * 
 * @param s The string to search.
 * @param c The character to be located.
 * 
 * @return The address of the last occurrence of the character c in the
 * string s.
 */
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (s[i] != c && i > 0)
		i--;
	if (s[i] == c)
		return (&((char *)s)[i]);
	return (NULL);
}
