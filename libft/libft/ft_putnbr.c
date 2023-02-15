/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:06:51 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/05 12:34:06 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It prints the number given as a parameter.
 * 
 * @param n the number to be printed
 */
void	ft_putnbr(int n)
{
	if (n > -2147483648)
	{
		if (n < 0)
		{
			ft_putchar('-');
			n = n * -1;
		}
		if (n >= 10)
		{
			ft_putnbr(n / 10);
			n = n % 10;
		}
		if (n < 10)
			ft_putchar(n + '0');
	}
	else
		ft_putstr("-2147483648");
}
