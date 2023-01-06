/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:22:07 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:27:47 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int nbr)
{
	char	*s;
	int		l;
	long	n;

	n = nbr;
	l = ft_intlen(n);
	s = (char *)malloc(sizeof(char) * l + 1);
	if (!s)
		return (NULL);
	s[l] = '\0';
	if (n < 0)
		n *= -1;
	while (l--)
	{
		s[l] = (n % 10) + 48;
		n /= 10;
	}
	if (nbr < 0)
		s[0] = '-';
	return (s);
}
