/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:10:01 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/08 17:29:03 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * If the strings are equal, return 1, otherwise return 0
 *
 * @param s1 The first string to be compared.
 * @param s2 "Hello"
 * @param n The maximum number of characters to compare.
 *
 * @return 1 if the strings are equal, otherwise it returns 0.
 */
int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	if (s1 && s2 && n > 0)
	{
		i = 0;
		while (i < n && (s1[i] != '\0' && s2[i] != '\0'))
		{
			if (s1[i] == s2[i])
				i++;
			else
				return (0);
		}
		if (s1[i] != s2[i] && i < n)
			return (0);
	}
	return (1);
}
