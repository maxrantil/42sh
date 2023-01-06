/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:46:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:28:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	initialize_data(const char *format, t_ftprintf *data, int flag)
{
	data->fmt = format;
	data->hold_str = NULL;
	if (!flag)
		data->char_count = 0;
	data->space_count = 0;
	data->astx_flag = 0;
	data->len_va_arg = 0;
	data->width = 0;
	data->width_check = 0;
	data->precision = 0;
	data->plus_flag = 0;
	data->minus_flag = 0;
	data->va_ret = 0;
	data->hash_flag = 0;
	data->zero = 0;
	data->zero_flag = 0;
	data->le_f = 0;
	data->for_plus = 0;
	data->precision_flag = 0;
	data->uint_check = 0;
	data->sign = 1;
}

void	check_parser(t_ftprintf *data)
{
	size_t	i;

	i = 0;
	while (FLAGS[i])
	{
		while (FLAGS[i] && FLAGS[i] != *data->fmt)
			i++;
		g_flag_disp_tbl[i](data);
		if (!data->sign)
			break ;
		i = 0;
	}
	i = 0;
	while (i < 6)
		g_check_disp_tbl[i++](data);
	i = 0;
	while (SPECIF[i] && SPECIF[i] != *data->fmt)
		i++;
	g_print_disp_tbl[i](data);
}

static void	parser_loop(t_ftprintf *data)
{
	while (*data->fmt)
	{
		if (*data->fmt == '{')
			write_colors(data);
		if (*data->fmt != '%')
		{
			data->char_count += write(1, data->fmt++, 1);
			continue ;
		}
		++data->fmt;
		check_parser(data);
		initialize_data(data->fmt, data, 1);
	}
}

int	ft_printf(const char *format, ...)
{
	t_ftprintf		data;

	va_start(data.ap, format);
	initialize_data(format, &data, 0);
	parser_loop(&data);
	va_end(data.ap);
	return ((int)data.char_count);
}
