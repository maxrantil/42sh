/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_astrix_procent.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:01:29 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:28:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_hex_length(t_ftprintf *data)
{
	if (*data->fmt == 'x' || *data->fmt == 'X')
		itoa_b((unsigned int)va_arg(data->ap, unsigned long long), 16, data);
	else if (*data->fmt == 'h' && (data->fmt[1] == 'x' || data->fmt[1] == 'X') \
		&& ++data->fmt)
		itoa_b((unsigned short)va_arg(data->ap, unsigned long long), 16, data);
	else if (*data->fmt == 'l' && (data->fmt[1] == 'x' || data->fmt[1] == 'X') \
		&& ++data->fmt)
		itoa_b(va_arg(data->ap, unsigned long), 16, data);
	else if (*data->fmt == 'h' && data->fmt[1] == 'h' \
		&& (data->fmt[2] == 'x' || data->fmt[2] == 'X'))
	{
		data->fmt += 2;
		itoa_b((unsigned char)va_arg(data->ap, unsigned long long), 16, data);
	}
	else if (*data->fmt == 'l' && data->fmt[1] == 'l' \
		&& (data->fmt[2] == 'x' || data->fmt[2] == 'X'))
	{
		data->fmt += 2;
		itoa_b(va_arg(data->ap, unsigned long long), 16, data);
	}
}

void	pf_print_hex_hash(t_ftprintf *data)
{
	if (*data->fmt == 'x')
		data->char_count += write(1, "0x", 2);
	else
		data->char_count += write(1, "0X", 2);
}

void	hex_print(t_ftprintf *data)
{
	if (data->zero_flag && data->precision_flag)
		ignore_zero_flag(data);
	data->width -= 2 * (data->hash_flag && data->width \
		&& (*data->fmt == 'x' || *data->fmt == 'X'));
	exec_flags_and_length(data);
	pf_write(data);
	if (data->minus_flag)
		exec_width(data);
	ft_strdel(&data->hold_str);
	data->fmt++;
}

void	print_procent(t_ftprintf *data)
{
	if (data->zero_flag && data->precision_flag)
		ignore_zero_flag(data);
	if (data->plus_flag && --data->char_count)
		data->plus_flag = 0;
	data->len_va_arg = 1;
	if (!data->minus_flag && data->width && !data->zero_flag)
		exec_width(data);
	if (ft_isalpha(*data->fmt) \
		&& data->space_count && !data->plus_flag)
		exec_flag_space(data);
	if (data->precision_flag)
		exec_precision(data);
	if (!data->plus_flag && data->zero_flag && !data->precision_flag)
		exec_flag_zero(data);
	data->char_count += write(1, data->fmt, 1);
	if (data->minus_flag)
		exec_width(data);
	data->fmt++;
}
