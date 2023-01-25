/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_filter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:26:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/05 11:08:05 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_arg_filter(t_arg *arg, t_flags *flags)
{
	int		ret;

	ret = 0;
	flags_correction(flags, arg->specifier);
	if (arg->specifier)
	{
		if (arg->specifier == 'c')
			ret += ft_char_convert(va_arg(arg->arg, signed int), flags);
		if (arg->specifier == 's')
			ret += ft_str_convert(va_arg(arg->arg, char *), flags);
		if (arg->specifier == 'b')
			ft_bin_print((size_t)va_arg(arg->arg, int), &ret);
		if (arg->specifier == 'r')
			non_printa_print(va_arg(arg->arg, int), &ret);
		if (arg->specifier == 'k')
			print_date((size_t)va_arg(arg->arg, int), &ret);
		if (arg->specifier == '%')
			ret += ft_char_convert('%', flags);
		if (ft_strchr("diouxXfp", arg->specifier))
			ret += ft_diouxf_convert(arg, flags);
	}
	return (ret);
}
