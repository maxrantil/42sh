/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_null_float_oct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:33:55 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:28:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putfloat(t_ftprintf *data)
{
	pf_exec_before_flags(data);
	if (data->sign < 0)
		data->char_count += write(1, "-", 1);
	data->char_count += write(1, data->hold_str, ft_strlen(data->hold_str));
	if (data->hash_flag && !data->precision && data->precision_flag)
		data->char_count += write(1, ".", 1);
}

static void	big_precision(long long hold, t_ftprintf *data)
{
	hold -= 200;
	while (hold--)
		data->char_count += write(1, "0", 1);
}

void	float_print(t_ftprintf *data)
{
	long long	hold;

	hold = 0;
	if (!data->precision_flag)
		data->precision = 6;
	if (data->precision > 200)
	{
		hold = data->precision;
		data->precision = 200;
	}
	if (data->le_f)
		conv_float_str(va_arg(data->ap, long double), data);
	else
		conv_float_str(va_arg(data->ap, double), data);
	exec_flags_and_length(data);
	pf_putfloat(data);
	if (hold)
		big_precision(hold, data);
	if (data->minus_flag)
		exec_width(data);
	ft_strdel(&data->hold_str);
	data->fmt++;
}

void	check_oct_length(t_ftprintf *data)
{
	if (*data->fmt == 'o')
		itoa_b((unsigned int)va_arg(data->ap, unsigned long long), 8, data);
	else if (*data->fmt == 'h' && data->fmt[1] == 'o' && ++data->fmt)
		itoa_b((unsigned short)va_arg(data->ap, unsigned long long), 8, data);
	else if (*data->fmt == 'l' && data->fmt[1] == 'o' && ++data->fmt)
		itoa_b((unsigned long)va_arg(data->ap, unsigned long long), 8, data);
	else if (*data->fmt == 'h' && data->fmt[1] == 'h' && data->fmt[2] == 'o')
	{
		data->fmt += 2;
		itoa_b((unsigned char)va_arg(data->ap, unsigned long long), 8, data);
	}
	else if (*data->fmt == 'l' && data->fmt[1] == 'l' && data->fmt[2] == 'o')
	{
		data->fmt += 2;
		itoa_b(va_arg(data->ap, unsigned long long), 8, data);
	}
	else if ((*data->fmt == 'L' || (*data->fmt == 'l' && data->fmt[1] == 'f')))
	{
		if (*data->fmt == 'L')
			data->le_f = 1;
		++data->fmt;
	}
}

void	oct_print(t_ftprintf *data)
{
	if (data->zero_flag && data->precision_flag)
		ignore_zero_flag(data);
	exec_flags_and_length(data);
	pf_write(data);
	if (data->minus_flag)
		exec_width(data);
	ft_strdel(&data->hold_str);
	data->fmt++;
}
