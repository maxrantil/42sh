/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:10:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/04 16:42:00 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flags_correction(t_flags *flags, char spec)
{
	if (flags->minus)
		flags->zero = 0;
	if (spec == 'd' || spec == 'i' || spec == 'u')
		flags->hash = 0;
	if (spec == 'u')
	{
		flags->space = 0;
		flags->plus = 0;
	}
	if (spec == 'd' || spec == 'i')
		if (flags->precision >= 0)
			flags->zero = 0;
	if (spec == 'o')
		if (flags->precision == 0 && flags->hash)
			flags->precision = 1;
	if (spec == 'x' || spec == 'X')
	{
		if (flags->precision == 0)
			flags->zero = 0;
		flags->space = 0;
	}
}

int	speci_correction(char specifier)
{
	char	c;

	c = specifier;
	if (c == 'c' || c == 's' || c == 'p')
		return (1);
	if (c == '%' || c == 'f' || c == 'b')
		return (1);
	if (c == 'd' || c == 'i' || c == 'r')
		return (1);
	if (c == 'o' || c == 'u' || c == 'k')
		return (1);
	if (c == 'x' || c == 'X')
		return (1);
	return (0);
}

char	*width_calculator(char *format, t_flags *flags, t_arg *arg)
{
	if (*format == '*')
	{
		flags->width = va_arg(arg->arg, int);
		if (flags->width < 0)
		{
			flags->width *= -1;
			flags->minus = 1;
		}
		format++;
	}
	if (*format >= '0' && *format <= '9')
		flags->width = 0;
	while (*format >= '0' && *format <= '9')
	{
		flags->width = flags->width * 10 + (*format - '0');
		format++;
	}
	return (format);
}

char	*precision_calculator(char *format, t_flags *flags, t_arg *arg)
{
	if (*format == '.')
	{
		flags->precision++;
		format++;
		while (*format >= '0' && *format <= '9')
		{
			flags->precision = flags->precision * 10 + (*format - '0');
			format++;
		}
		if (*format == '*')
		{
			flags->precision = va_arg(arg->arg, int);
			if (flags->precision < 0)
				flags->precision = -1;
			format++;
		}
	}
	return (format);
}
