/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:04:07 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/07 18:10:55 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		i++;
	if (nb < 0)
	{
		nb = nb * -1;
		i++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static void	ft_int_to_char(char *ret, long nb, int len)
{
	ret[len] = '\0';
	if (nb == 0)
	{
		ret[0] = '0';
		return ;
	}
	if (nb < 0)
	{
		ret[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		len--;
		ret[len] = (nb % 10) + '0';
		nb = nb / 10;
	}
}

/**
 * It converts an integer to a string.
 * 
 * @param nb the number to convert
 * 
 * @return A pointer to a string.
 */
char	*ft_itoa(int nb)
{
	int		len;
	char	*ret;

	len = ft_len((long)nb);
	ret = (char *)ft_memalloc(sizeof(char) * (len + 1));
	if (ret)
	{
		ft_int_to_char(ret, (long)nb, len);
		return (ret);
	}
	return (NULL);
}
