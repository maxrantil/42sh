/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_write_flags.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:16:28 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:28:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_write(t_ftprintf *data)
{
	if (*data->fmt != 'u' && (*data->hold_str == '-' || data->plus_flag))
		pf_exec_before_flags(data);
	data->char_count -= ((*data->fmt == 'u') && (data->plus_flag > 0));
	if (*data->fmt == 'o' && *data->hold_str == '0' && data->precision_flag \
		&& !data->precision && !data->hash_flag && !data->astx_flag)
		return ;
	else if (*data->fmt == 'p' && *data->hold_str == '0' \
		&& data->precision_flag && !data->precision && !data->astx_flag)
		return ;
	else if (*data->fmt != 'o' && *data->hold_str == '0' \
		&& data->precision_flag && !data->precision && !data->astx_flag)
		return ;
	else if (*data->hold_str == '-' && (*data->fmt == 'd' || *data->fmt == 'i'))
		data->char_count += \
		write(1, data->hold_str + 1, ft_strlen(data->hold_str) - 1);
	else
		data->char_count += write(1, data->hold_str, ft_strlen(data->hold_str));
}

void	pf_exec_before_flags(t_ftprintf *data)
{
	if (*data->hold_str == '-')
	{
		if (data->plus_flag && !data->minus_flag && --data->char_count)
			data->plus_flag = 0;
		exec_precision(data);
		exec_flag_zero(data);
	}
	else if (data->plus_flag)
	{
		ft_putchar('+');
		data->for_plus = 1;
		data->plus_flag = 0;
		exec_precision(data);
		exec_flag_zero(data);
	}
}

static void	zero_under_flags(t_ftprintf *data)
{
	if (!data->uint_check && ft_isalpha(*data->fmt) \
			&& data->space_count && !data->plus_flag)
		exec_flag_space(data);
	if (data->hash_flag && *data->hold_str != '0' \
		&& (*data->fmt == 'x' || *data->fmt == 'X'))
		pf_print_hex_hash(data);
	if (data->hash_flag && *data->hold_str != '0' && *data->fmt == 'o')
		data->char_count += write(1, "0", 1);
	if (data->precision_flag)
		exec_precision(data);
	if (!data->plus_flag && data->zero_flag && !data->precision_flag)
		exec_flag_zero(data);
}	

void	exec_flags_and_length(t_ftprintf *data)
{
	data->len_va_arg = ft_strlen(data->hold_str);
	data->len_va_arg += (data->hash_flag && *data->fmt == 'o');
	data->len_va_arg += (data->hash_flag && !data->precision \
		&& data->precision_flag && *data->fmt == 'f');
	if (!data->minus_flag && data->width && !data->zero_flag)
		exec_width(data);
	if (data->va_ret >= 0)
		zero_under_flags(data);
	if (*data->hold_str == '-')
	{
		data->char_count += write(1, "-", 1);
		if (data->plus_flag && data->minus_flag && data->va_ret < 0)
			data->char_count--;
	}
}
