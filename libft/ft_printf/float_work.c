/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:59:54 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:28:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	nine_rouning(char *mantissa, int i, t_ftprintf *data)
{
	long long	new_unit;

	mantissa[--i] = '0';
	while (i-- && mantissa[i] == '9')
		mantissa[i] = '0';
	if (i >= 0)
		mantissa[i] += 1;
	else
	{
		new_unit = ft_atoi(data->hold_str);
		ft_strdel(&data->hold_str);
		itoa_b(new_unit + 1, 10, data);
	}
}

static int	bankers_rounding(long double nbr, char last_digit, t_ftprintf *data)
{
	int	res;

	res = 0;
	nbr -= (long long)nbr;
	if (nbr > 0.5)
		res++;
	else if (nbr == 0.5)
		res = ((last_digit + 1 * data->sign) % 2 == 0);
	return (res);
}

static char	*join_unit_mant(char *mantissa, size_t x, t_ftprintf *data)
{
	char	*combo;
	int		i;
	int		j;

	j = 0;
	i = 0;
	combo = ft_strnew(ft_strlen(data->hold_str) + ft_strlen(mantissa) + 1);
	if (!combo)
		exit(1);
	while (data->hold_str[i])
		combo[j++] = data->hold_str[i++];
	if (data->precision || x == 6)
		combo[j++] = '.';
	i = 0;
	while (mantissa[i])
		combo[j++] = mantissa[i++];
	ft_strdel(&data->hold_str);
	ft_strdel(&mantissa);
	return (combo);
}

static char	*mant_to_a(long double nbr, t_ftprintf *data)
{
	char		*mantissa;
	int			i;
	size_t		x;
	int			round_up;

	i = 0;
	mantissa = ft_strnew(data->precision);
	x = 0;
	while (data->precision > x)
	{
		nbr *= 10;
		mantissa[i++] = ((long long)nbr % 10) + 48;
		nbr -= (long long)nbr;
		x++;
	}
	round_up = bankers_rounding(nbr, mantissa[i - 1], data);
	if (round_up && mantissa[i - 1] == '9')
		nine_rouning(mantissa, i, data);
	else
		mantissa[i - 1] += round_up;
	return (join_unit_mant(mantissa, x, data));
}

void	conv_float_str(long double nbr, t_ftprintf *data)
{
	int			round_up;
	long long	last_digit;

	data->sign = 1 - 2 * (nbr < 0 || (1 / nbr < 0 && nbr == 0));
	if (nbr < 0 || (1 / nbr < 0 && nbr == 0))
	{
		nbr *= -1;
		data->width -= (data->width > 0);
	}
	if (!data->precision && data->precision_flag)
	{
		last_digit = (long long)nbr % 10;
		round_up = bankers_rounding(nbr, last_digit + 48, data) * data->sign;
		itoa_b((long long)nbr + round_up, 10, data);
	}
	else
	{
		itoa_b((long long)nbr, 10, data);
		data->hold_str = mant_to_a(nbr, data);
	}
}
