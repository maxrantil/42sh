/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:30:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:28:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_signed_length(t_ftprintf *data)
{
	if (*data->fmt == 'd' || *data->fmt == 'i')
		data->hold_str = conv_to_str((int)va_arg(data->ap, long long), data);
	else if (*data->fmt == 'h' && (data->fmt[1] == 'd' || data->fmt[1] == 'i') \
		&& ++data->fmt)
		data->hold_str = conv_to_str((short)va_arg(data->ap, long long), data);
	else if (*data->fmt == 'l' && (data->fmt[1] == 'd' || data->fmt[1] == 'i') \
		&& ++data->fmt)
		data->hold_str = conv_to_str((long)va_arg(data->ap, long long), data);
	else if (*data->fmt == 'h' && data->fmt[1] == 'h' \
		&& (data->fmt[2] == 'd' || data->fmt[2] == 'i'))
	{
		data->fmt += 2;
		data->hold_str = conv_to_str((char)va_arg(data->ap, long long), data);
	}
	else if (*data->fmt == 'l' && data->fmt[1] == 'l' \
		&& (data->fmt[2] == 'd' || data->fmt[2] == 'i'))
	{
		data->fmt += 2;
		data->hold_str = conv_to_str(va_arg(data->ap, long long), data);
	}
}

static long long	pf_nbrlen(long long nbr)
{
	int	c;

	c = 0;
	if (nbr < 0 && ++c)
		nbr *= -1;
	while (nbr > 9 && ++c)
		nbr /= 10;
	return (++c);
}

char	*conv_to_str(long long nbr, t_ftprintf *data)
{
	char		*str;
	long long	l;

	data->va_ret = nbr;
	l = pf_nbrlen(nbr);
	str = (char *)malloc(sizeof(char) * l + 1);
	if (!str)
		exit(1);
	str[l] = '\0';
	if (nbr < 0)
		nbr *= -1;
	while (l--)
	{
		str[l] = nbr % 10 + 48;
		nbr /= 10;
	}
	if (data->va_ret < 0)
		str[0] = '-';
	if (!ft_strcmp(str, "-'..--).0-*(+,))+(0(") || !ft_strcmp(str, "-("))
	{
		ft_strdel(&str);
		return (ft_strdup("-9223372036854775808"));
	}
	return (str);
}

void	int_print(t_ftprintf *data)
{
	if (data->zero_flag && data->precision_flag)
		ignore_zero_flag(data);
	exec_flags_and_length(data);
	pf_write(data);
	if (data->minus_flag)
		exec_width(data);
	ft_strdel(&data->hold_str);
	data->fmt++;
}

void	address_print(t_ftprintf *data)
{
	itoa_b(va_arg(data->ap, long long unsigned), 16, data);
	data->len_va_arg = ft_strlen(data->hold_str);
	if (data->width)
		data->width -= 2;
	if (!data->minus_flag && data->width)
		exec_width(data);
	data->char_count += write(1, "0x", 2);
	pf_write(data);
	if (data->minus_flag)
		exec_width(data);
	ft_strdel(&data->hold_str);
	data->fmt++;
}
