/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:19:03 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/04 16:41:39 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_bin_print(size_t nbr, int *ret)
{
	if (nbr > 1)
		ft_bin_print(nbr / 2, ret);
	else
		ret[0] += ft_printf("0");
	ret[0] += ft_printf("%i", nbr % 2);
}

void	non_printa_print(char val, int *ret)
{
	if (val == 9)
		*ret += write(1, "\\t", 2);
	if (val == 10)
		*ret += write(1, "\\n", 2);
	if (val == 11)
		*ret += write(1, "\\v", 2);
	if (val == 12)
		*ret += write(1, "\\f", 2);
	if (val == 13)
		*ret += write(1, "\\r", 2);
}

void	print_date(size_t date, int *ret)
{
	int	day;
	int	month;
	int	year;

	day = date / 1000000;
	month = (date / 10000) % 100;
	year = date % 10000;
	if ((day > 0 && day <= 31) && (month > 0 && month <= 12))
	{
		*ret += ft_printf("%i-", year);
		if (month < 10)
			*ret += write(1, "0", 1);
		*ret += ft_printf("%i-", month);
		if (day < 10)
			*ret += write(1, "0", 1);
		*ret += ft_printf("%i", day);
	}
}
