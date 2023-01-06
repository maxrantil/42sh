/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:32:09 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:28:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	exec_precision_str(t_ftprintf *data)
{
	long	sub;

	sub = data->precision;
	if (data->precision)
	{
		while ((size_t)sub-- > data->len_va_arg)
			data->char_count += write(1, "0", 1);
	}
}

void	str_precision_width(t_ftprintf *data)
{
	long	sub;

	sub = 0;
	sub *= (data->astx_flag);
	if (data->precision && !data->width)
	{
		if (data->precision < data->len_va_arg)
			data->precision = data->len_va_arg;
		sub += data->width - data->precision;
		sub *= (sub > 0);
		while (sub--)
			data->char_count += write(1, " ", 1);
	}
	else if (data->width)
	{
		sub += data->width;
		sub *= (sub > 0);
		while ((size_t)sub-- > data->len_va_arg)
			data->char_count += write(1, " ", 1);
	}
}

static void	pf_write_str(t_ftprintf *data)
{
	if (data->precision && data->precision < data->len_va_arg)
		data->len_va_arg = data->precision;
	if (!data->minus_flag)
		str_precision_width(data);
	if (!data->precision && data->precision_flag && !data->astx_flag)
		data->char_count += write(1, "", 0);
	else
		data->char_count += write(1, data->hold_str, data->len_va_arg);
	if (data->minus_flag)
		str_precision_width(data);
}

void	str_print(t_ftprintf *data)
{
	data->hold_str = va_arg(data->ap, char *);
	if (data->hold_str == NULL)
		data->hold_str = "(null)";
	data->len_va_arg = ft_strlen(data->hold_str);
	if ((!data->precision && data->precision_flag) \
		&& data->width && !data->astx_flag)
	{
		while (data->width--)
			data->char_count += write(1, " ", 1);
		data->fmt++;
		return ;
	}
	pf_write_str(data);
	data->fmt++;
}

void	char_print(t_ftprintf *data)
{
	if (!data->minus_flag && data->width)
		exec_width(data);
	ft_putchar((char)va_arg(data->ap, int));
	++data->char_count;
	if (data->minus_flag)
		exec_width(data);
	data->fmt++;
}
