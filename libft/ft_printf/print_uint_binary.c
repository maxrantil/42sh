/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint_binary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:33:03 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:28:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_unsigned_length(t_ftprintf *data)
{
	if (*data->fmt == 'u')
		data->hold_str = uint_str(\
			(unsigned int)va_arg(data->ap, unsigned long long), data);
	else if (*data->fmt == 'h' && data->fmt[1] == 'u' && ++data->fmt)
		data->hold_str = uint_str(\
			(unsigned short)va_arg(data->ap, unsigned long long), data);
	else if (*data->fmt == 'l' && data->fmt[1] == 'u' && ++data->fmt)
		data->hold_str = uint_str(\
			(unsigned long)va_arg(data->ap, unsigned long long), data);
	else if (*data->fmt == 'h' && data->fmt[1] == 'h' && data->fmt[2] == 'u')
	{
		data->fmt += 2;
		data->hold_str = uint_str(\
			(unsigned char)va_arg(data->ap, unsigned long long), data);
	}
	else if (*data->fmt == 'l' && data->fmt[1] == 'l' && data->fmt[2] == 'u')
	{
		data->fmt += 2;
		data->hold_str = uint_str(va_arg(data->ap, unsigned long long), data);
	}
}

static int	uint_nbrlen(unsigned long long nbr)
{
	int	c;

	c = 0;
	while (nbr > 9 && ++c)
		nbr = nbr / 10;
	return (++c);
}

char	*uint_str(unsigned long long nbr, t_ftprintf *data)
{
	char	*str;
	int		l;

	data->va_u_ret = nbr;
	l = uint_nbrlen(nbr);
	str = (char *)malloc(sizeof(char) * l + 1);
	if (!str)
		exit(1);
	str[l] = '\0';
	while (l--)
	{
		str[l] = nbr % 10 + 48;
		nbr /= 10;
	}
	return (str);
}

void	uint_print(t_ftprintf *data)
{
	data->uint_check = 1;
	if (data->zero_flag && data->precision_flag)
		ignore_zero_flag(data);
	exec_flags_and_length(data);
	pf_write(data);
	if (data->minus_flag)
		exec_width(data);
	ft_strdel(&data->hold_str);
	data->fmt++;
}

void	binary_print(t_ftprintf *data)
{
	itoa_b(va_arg(data->ap, long long), 2, data);
	exec_flags_and_length(data);
	pf_write(data);
	if (data->minus_flag)
		exec_width(data);
	ft_strdel(&data->hold_str);
	data->fmt++;
}
