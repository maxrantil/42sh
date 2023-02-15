/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa.base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:09:23 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/17 17:22:04 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_char_val(unsigned long long int val)
{
	char	ret;

	if (val >= 10)
		ret = (val - 10) + 'a';
	else
		ret = val + '0';
	return (ret);
}

static int	ft_deci_len(unsigned long long int val, int base)
{
	int	len;

	len = 0;
	while (val != 0)
	{
		len++;
		val /= base;
	}
	return (len);
}

/**
 * It converts a long long int to a string in a given base
 * 
 * @param value the number to be converted
 * @param base the base to convert to
 * 
 * @return A string of the value in the base given.
 */
char	*ft_llitoa_base(long long int value, int base)
{
	int						len;
	unsigned long long int	tmp;
	char					*ret;

	len = 0;
	if (value < 0 && base == 10)
	{
		tmp = value * -1;
		len++;
	}
	else
		tmp = (unsigned long long int)value;
	len += ft_deci_len(tmp, base);
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	while (tmp)
	{
		ret[--len] = ft_char_val(tmp % base);
		tmp /= base;
	}
	if (value < 0 && base == 10)
		ret[--len] = '-';
	return (ret);
}
