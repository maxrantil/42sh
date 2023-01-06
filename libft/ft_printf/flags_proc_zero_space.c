/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_proc_zero_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:05:47 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:28:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	exec_flag_space(t_ftprintf *data)
{
	if (ft_isalpha(*data->fmt) && data->space_count && !data->plus_flag)
		data->char_count += write(1, " ", 1);
}

void	get_flag_space(t_ftprintf *data)
{
	while (*data->fmt == ' ' && ++data->space_count)
		data->fmt++;
}

void	exec_flag_zero(t_ftprintf *data)
{
	long	sub;

	sub = data->zero;
	sub += (data->width > 0 && data->zero_flag > 0) * data->width;
	sub *= (!data->astx_flag);
	if (*data->fmt == 'x' || *data->fmt == 'X')
		sub -= (data->hash_flag > 0) * 2;
	sub -= (data->for_plus > 0 || data->space_count > 0);
	sub *= (sub > 0);
	while ((size_t)sub-- > data->len_va_arg)
		data->char_count += write(1, "0", 1);
}

void	get_flag_zero(t_ftprintf *data)
{
	if (*data->fmt == '0')
	{
		while (*data->fmt == '0')
			data->fmt++;
		if (!data->minus_flag)
		{
			data->zero_flag = 1;
			data->zero = get_it(data);
		}
	}
}
