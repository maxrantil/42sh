/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_itoa_b_getit_nullprint.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:14:00 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:28:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	null_print(t_ftprintf *data)
{
	data->sign = 0;
}

void	ignore_zero_flag(t_ftprintf *data)
{
	data->zero_flag = 0;
	data->width = data->zero;
	data->zero = 0;
}

size_t	get_it(t_ftprintf *data)
{
	size_t	c_single;
	size_t	ret;

	c_single = 0;
	ret = 0;
	data->width_check = 1;
	while (ft_isdigit(*data->fmt) && ++c_single)
	{
		if (c_single == 1 && ++c_single)
			ret = *data->fmt - 48;
		else
			ret = ret * 10 + (*data->fmt - 48);
		data->fmt++;
	}
	return (ret);
}

static int	pf_intlen(unsigned long long nbr, unsigned int base)
{
	int	count;

	count = 0;
	if (!nbr)
		return (1);
	while (nbr)
	{
		nbr /= base;
		count++;
	}
	return (count);
}

void	itoa_b(unsigned long long nbr, \
	unsigned int base, t_ftprintf *data)
{
	unsigned long long	l;

	l = pf_intlen(nbr, base);
	data->hold_str = (char *)ft_strnew(l);
	if (!data->hold_str)
		exit(1);
	while (l--)
	{
		if ((*data->fmt == 'x' || *data->fmt == 'p') && nbr % base > 9)
			data->hold_str[l] = (char)(nbr % base) + 87;
		else if (*data->fmt == 'X' && nbr % base > 9)
			data->hold_str[l] = (char)(nbr % base) + 55;
		else
			data->hold_str[l] = (char)(nbr % base) + 48;
		nbr /= base;
	}
}
