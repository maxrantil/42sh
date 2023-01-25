/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:09:23 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/17 17:22:25 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_char_val(unsigned long long val)
{
	char	ret;

	if (val >= 10)
		ret = (val - 10) + 'a';
	else
		ret = val + '0';
	return (ret);
}

static int	ft_deci_len(unsigned long long val, int base)
{
	int	len;

	len = 0;
	if (val == 0)
		len++;
	while (val != 0)
	{
		len++;
		val /= base;
	}
	return (len);
}

static void	catch_negative(int *len, long long val, int base, char *ret)
{
	if (!ret)
	{
		if (val < 0 && base == 10)
			*len = *len + 1;
	}
	else
	{
		if (val < 0 && base == 10)
			ret[0] = '-';
		if (val == 0)
			ret[0] = '0';
	}
}

static int	if_neg(long long value, unsigned long long *tmp, int base)
{
	int	ret;

	ret = 0;
	if (value < 0 && base == 10)
	{
		*tmp = value * -1;
		ret++;
	}
	else
		*tmp = (unsigned long long)value;
	return (ret);
}

/**
 * It converts a long long to a string in a given base
 * 
 * @param value the number to be converted
 * @param base the base of the number
 * 
 * @return A string of the value in the base given.
 */
char	*ft_lltoa_base(long long value, int base)
{
	int					len;
	unsigned long long	tmp;
	char				*ret;

	ret = NULL;
	if (value < -9223372036854775807 && base == 10)
		return (ft_strdup("-9223372036854775808"));
	len = if_neg(value, &tmp, base);
	len += ft_deci_len(tmp, base);
	catch_negative(&len, value, base, ret);
	ret = (char *)ft_memalloc(sizeof(char) * (len + 1));
	ret[len] = '\0';
	while (tmp)
	{
		ret[--len] = ft_char_val(tmp % base);
		tmp /= base;
	}
	catch_negative(&len, value, base, ret);
	return (ret);
}
