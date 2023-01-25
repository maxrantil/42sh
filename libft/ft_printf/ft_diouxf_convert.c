/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diouxf_convert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 16:17:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/04 16:41:47 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*option_a(t_arg *arg, t_flags *flags)
{
	if (arg->specifier == 'd' || arg->specifier == 'i')
	{
		if (flags->mod == 1)
			return (ft_itoa_base((short)va_arg(arg->arg, int), 10));
		if (flags->mod == 2)
			return (ft_itoa_base((signed char)va_arg(arg->arg, int), 10));
		if (flags->mod == 3)
			return (ft_ltoa_base(va_arg(arg->arg, long), 10));
		if (flags->mod == 5)
			return (ft_lltoa_base(va_arg(arg->arg, long long), 10));
		return (ft_itoa_base(va_arg(arg->arg, int), 10));
	}
	if (flags->mod == 1)
		return (ft_ulltoa_base((unsigned short)va_arg(arg->arg, int), 10));
	if (flags->mod == 2)
		return (ft_ulltoa_base((unsigned char)va_arg(arg->arg, int), 10));
	if (flags->mod == 3)
		return (ft_ulltoa_base(va_arg(arg->arg, unsigned long long), 10));
	if (flags->mod == 5)
		return (ft_ulltoa_base(va_arg(arg->arg, unsigned long long), 10));
	return (ft_ulltoa_base(va_arg(arg->arg, unsigned int), 10));
}

static char	*option_b(t_arg *arg, t_flags *flags)
{
	if (arg->specifier == 'p')
		return (ft_ulltoa_base(va_arg(arg->arg, unsigned long long), 16));
	if (flags->mod == 1)
		return (ft_itoa_base((unsigned short)va_arg(arg->arg, int), 8));
	if (flags->mod == 2)
		return (ft_itoa_base((unsigned char)va_arg(arg->arg, int), 8));
	if (flags->mod == 3)
		return (ft_ltoa_base(va_arg(arg->arg, long), 8));
	if (flags->mod == 5)
		return (ft_lltoa_base(va_arg(arg->arg, long long), 8));
	return (ft_itoa_base(va_arg(arg->arg, int), 8));
}

static char	*option_c(t_arg *arg, t_flags *flags)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	if (flags->mod == 0)
		str = ft_itoa_base(va_arg(arg->arg, int), 16);
	if (flags->mod == 1)
		str = ft_itoa_base((unsigned short)va_arg(arg->arg, int), 16);
	if (flags->mod == 2)
		str = ft_itoa_base((unsigned char)va_arg(arg->arg, int), 16);
	if (flags->mod == 3)
		str = ft_ltoa_base(va_arg(arg->arg, long), 16);
	if (flags->mod == 5)
		str = ft_lltoa_base(va_arg(arg->arg, long long), 16);
	if (arg->specifier == 'X' && str)
	{
		tmp = str;
		while (*tmp != '\0')
		{
			*tmp = ft_toupper(*tmp);
			tmp++;
		}
	}
	return (str);
}

static char	*option_f(t_arg *arg, t_flags *flags)
{
	char			*str;
	size_t			precision;

	str = NULL;
	if (flags->precision >= 0)
		precision = (size_t)flags->precision;
	else
		precision = 6;
	if (flags->mod == 4)
		str = ft_lftoa(va_arg(arg->arg, long double), precision);
	else
		str = ft_ftoa(va_arg(arg->arg, double), precision);
	return (str);
}

int	ft_diouxf_convert(t_arg *arg, t_flags *flags)
{
	int		ret;
	char	*str;

	ret = 0;
	str = NULL;
	if (arg->specifier == 'd' || arg->specifier == 'i' || arg->specifier == 'u')
		str = option_a(arg, flags);
	if (arg->specifier == 'o' || arg->specifier == 'p')
		str = option_b(arg, flags);
	if (arg->specifier == 'x' || arg->specifier == 'X')
		str = option_c(arg, flags);
	if (arg->specifier == 'f')
		str = option_f(arg, flags);
	if (str)
		ret += ft_diouxf_printer(str, flags, arg->specifier);
	return (ret);
}
