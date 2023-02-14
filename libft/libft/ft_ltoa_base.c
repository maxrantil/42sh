/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:47:32 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/17 17:26:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_char_val(unsigned long val)
{
	char	ret;

	if (val >= 10)
		ret = (val - 10) + 'a';
	else
		ret = val + '0';
	return (ret);
}

static int	ft_deci_len(unsigned long val, int base)
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

static void	catch_negative(int *len, long val, int base, char *ret)
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

/**
 * It converts a long to a string in a given base
 * 
 * @param value the number to be converted
 * @param base the base to convert to
 * 
 * @return A string of the value in the base given.
 */
char	*ft_ltoa_base(long value, int base)
{
	int				len;
	unsigned long	tmp;
	char			*ret;

	len = 0;
	ret = NULL;
	if (value < 0 && base == 10)
		tmp = value * -1;
	else
		tmp = (unsigned long)value;
	catch_negative(&len, value, base, ret);
	len += ft_deci_len(tmp, base);
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
