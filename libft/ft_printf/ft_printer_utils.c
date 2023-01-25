/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:58:12 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/04 16:41:50 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	attr_init(t_attr *attr)
{
	attr->nan = false;
	attr->inf = false;
	attr->zero = false;
	attr->padd_len = 0;
	attr->padd = NULL;
	attr->width = NULL;
	attr->str = NULL;
}

void	attr_parse(char *str, t_attr *attr, t_flags *flags, char spec)
{
	if (ft_strcmp("0", str) == 0)
	{
		attr->zero = true;
		if (spec != 'f' && flags->precision != 0)
			flags->hash = 0;
	}
	if (ft_strcmp("nan", str) == 0)
	{
		attr->nan = true;
		flags->zero = 0;
	}
	if (ft_strstr(str, "inf"))
	{
		attr->inf = true;
		flags->zero = 0;
	}
}

char	*str_correction(char *str, t_flags *flags, t_attr *attr, char speci)
{
	char	*tmp;

	if (flags->precision == 0 && speci == 'f'
		&& flags->hash && !attr->nan && !attr->inf)
		str = strjoin_head(str, ".");
	if (!attr->nan)
	{
		attr->padd = padding(flags, str, speci, attr->zero);
		if (attr->padd)
			if (speci == 'o')
				attr->padd_len = ft_strlen(attr->padd);
		if (!attr->inf)
				str = precision(str, flags->precision, attr->padd_len);
	}
	if (*str == '-')
	{
		tmp = str;
		str = ft_strdup(&str[1]);
		free(tmp);
	}
	attr->width = di_width_printer(flags, str, attr, speci);
	if (!flags->zero && attr->padd)
		str = strjoin_tail(attr->padd, str);
	return (str);
}

bool	precision_util(char *ret, int *precision, int *len, char *str)
{
	static bool	sign;

	if (!sign)
		sign = false;
	if (*len)
	{
		*len -= 1;
		ret[*precision] = str[*len];
		*precision -= 1;
		if (ret[*precision + 1] == '-')
		{
			ret[*precision + 1] = '0';
			sign = true;
		}	
	}
	else
	{
		ret[*precision] = '0';
		*precision -= 1;
	}
	return (sign);
}
