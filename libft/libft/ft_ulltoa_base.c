/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:16:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/17 17:48:49 by mbarutel         ###   ########.fr       */
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

/**
 * It converts an unsigned long long to a string in a given base
 * 
 * @param value the number to be converted
 * @param base the base of the number you want to convert to.
 * 
 * @return A string of the unsigned long long value in the base given.
 */
char	*ft_ulltoa_base(unsigned long long value, int base)
{
	int					len;
	unsigned long long	tmp;
	char				*ret;

	tmp = value;
	len = ft_deci_len(tmp, base);
	ret = (char *)ft_memalloc(sizeof(char) * (len + 1));
	ret[len] = '\0';
	while (tmp)
	{
		ret[--len] = ft_char_val(tmp % base);
		tmp /= base;
	}
	if (value == 0)
		ret[--len] = '0';
	return (ret);
}
