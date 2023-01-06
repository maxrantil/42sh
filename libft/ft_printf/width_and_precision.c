/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:16:11 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/24 19:10:25 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_precision(t_ftprintf *data)
{
	int	hold;

	hold = 0;
	if (*data->fmt == '.')
	{
		data->precision_flag = 1;
		data->fmt++;
		if (*data->fmt == '*')
		{
			hold = va_arg(data->ap, int);
			if (hold < 0)
			{
				hold *= 0;
				data->astx_flag = 1;
				data->precision = hold;
			}
			else
				data->precision = hold;
			data->fmt++;
		}
		else
			data->precision = get_it(data);
	}
}

void	check_width(t_ftprintf *data)
{
	int	hold;

	hold = 0;
	if (*data->fmt == '*')
	{
		hold = va_arg(data->ap, int);
		if (hold < 0)
		{
			data->astx_flag = 1;
			data->width_check = 1;
			data->minus_flag = 1;
			hold *= -1;
			data->width = hold;
		}
		else
			data->width = hold;
		data->fmt++;
	}
	if (ft_isdigit(*data->fmt) && (!data->zero_flag || data->width_check))
		data->width = get_it(data);
}

void	exec_precision(t_ftprintf *data)
{
	long	sub;

	sub = data->precision;
	if (data->precision && !data->plus_flag && *data->fmt != '%')
	{
		sub += (data->va_ret < 0);
		while ((size_t)sub-- > data->len_va_arg)
			data->char_count += write(1, "0", 1);
	}
}

static void	pf_exec_precision_with_width(t_ftprintf *data)
{
	long	sub;

	sub = 0;
	if (data->precision < data->len_va_arg)
	{
		sub += data->width - data->len_va_arg;
		sub += (data->va_ret < 0);
	}
	else
		sub += data->width - data->precision;
	sub -= (data->va_ret < 0 || data->plus_flag || data->space_count \
		|| (data->minus_flag && data->for_plus));
	sub *= (sub > 0);
	while (sub--)
		data->char_count += write(1, " ", 1);
}

void	exec_width(t_ftprintf *data)
{
	long	sub;

	sub = 0;
	if (data->precision)
		pf_exec_precision_with_width(data);
	else
	{
		sub -= (data->for_plus > 0);
		sub += (data->precision_flag && !data->precision);
		sub -= ((data->plus_flag > 0 && data->va_ret > 0) \
			|| data->space_count > 0 || *data->fmt == 'c');
		sub += data->width;
		sub -= ((((*data->fmt == 'f' || (((*data->fmt == 'd' \
					|| *data->fmt == 'i') && data->va_ret != 0)) \
					|| ((*data->fmt == 'x' || *data->fmt == 'X') \
					&& ft_strcmp(data->hold_str, "0")))) \
					&& data->precision_flag && !data->precision));
		sub *= (sub > 0);
		while ((size_t)sub-- > data->len_va_arg)
			data->char_count += write(1, " ", 1);
	}
}
