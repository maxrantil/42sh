/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_plus_minus_hash_null.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:05:47 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:28:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	null_flag(t_ftprintf *data)
{
	data->sign = 0;
}

void	hash_flag(t_ftprintf *data)
{
	if (*data->fmt == '#')
	{
		data->hash_flag = 1;
		data->fmt++;
	}
}

void	flag_minus(t_ftprintf *data)
{
	if (*data->fmt == '-')
	{
		if (data->zero_flag)
			data->zero_flag = 0;
		data->minus_flag = 1;
		data->fmt++;
	}
}

void	flag_plus(t_ftprintf *data)
{
	if (*data->fmt == '+')
	{
		if (data->plus_flag)
			data->char_count--;
		data->plus_flag = 1;
		data->fmt++;
		data->char_count++;
	}
}
