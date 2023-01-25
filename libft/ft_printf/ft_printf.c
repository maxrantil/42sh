/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:56:15 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/17 18:00:15 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	Initialises both structs
*/
static void	ft_init_struct(t_flags *flags)
{
	flags->mod = 0;
	flags->hash = 0;
	flags->zero = 0;
	flags->plus = 0;
	flags->minus = 0;
	flags->width = 0;
	flags->space = 0;
	flags->precision = -1;
}

/*
	Assigns the int value within modifier struct depending on the modifer
	and will return current index position.
*/
static char	*ft_modifier_check(char *format, t_flags *flags)
{
	if ((ft_strncmp(format, "h", 1) == 0))
		flags->mod = 1;
	if ((ft_strncmp(format, "hh", 2) == 0))
		flags->mod = 2;
	if ((ft_strncmp(format, "l", 1) == 0))
		flags->mod = 3;
	if ((ft_strncmp(format, "L", 1) == 0))
		flags->mod = 4;
	if ((ft_strncmp(format, "ll", 2) == 0))
		flags->mod = 5;
	while (*format == 'l' || *format == 'h' || *format == 'L')
		format++;
	return (format);
}

/*
	If one of the flag characters is found, it increments the value in the struct
*/
static char	*ft_flags_check(char *format, t_flags *flags, t_arg *arg)
{
	format++;
	while (*format == '#' || *format == '0'
		|| *format == '+' || *format == '-' || *format == ' ')
	{
		if (*format == '-')
			flags->minus++;
		if (*format == '#')
			flags->hash++;
		if (*format == '0')
			flags->zero++;
		if (*format == '+')
			flags->plus++;
		if (*format == ' ')
			flags->space++;
		format++;
	}
	format = width_calculator(format, flags, arg);
	format = precision_calculator(format, flags, arg);
	return (format);
}

static char	*arg_handler(char *format, t_flags *flags,
t_arg *arg, int *char_count)
{
	ft_init_struct(flags);
	format = ft_flags_check(format, flags, arg);
	format = ft_modifier_check(format, flags);
	arg->specifier = *format;
	if (speci_correction(*format))
		char_count[0] += ft_arg_filter(arg, flags);
	else
		if (*format != '\0')
			char_count[0] += write(1, format, 1);
	return (format);
}

/*
	Initilizes the list
	Prints characters that are not %
	When % is encountered, ft_flag_check 
	is called to collect all the flags and the specifier
*/
int	ft_printf(const char *restrict format, ...)
{
	t_arg		arg[1];
	t_flags		flags[1];
	int			char_count;

	char_count = 0;
	va_start(arg->arg, format);
	while (*format != '\0')
	{
		if (*format == '{')
			format = coloring((char *)format, &char_count);
		if (*format != '%')
		{
			if (*format != '\0')
				char_count += write(1, format, 1);
		}
		else
			format = arg_handler((char *)format, flags, arg, &char_count);
		if (*format != '\0')
			format++;
	}
	va_end(arg->arg);
	return (char_count);
}
