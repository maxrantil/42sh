/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:49:11 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:27:47 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	if (!n)
		return (1);
	i = 0;
	while (--n && s1[i] == s2[i] && (s1[i] || s2[i]))
		i++;
	if (s1[i] - s2[i] == 0)
		return (1);
	return (0);
}
