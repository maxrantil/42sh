/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lftoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 08:37:40 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/17 17:21:45 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*joiner(char *sign, char *str, long *base)
{
	char	*tmp;
	char	*base_str;

	tmp = str;
	base_str = ft_ltoa_base(base[0], 10);
	str = ft_strjoin(base_str, str);
	free(tmp);
	free(base_str);
	if (sign)
	{
		tmp = str;
		str = ft_strjoin(sign, str);
		free(tmp);
		free(sign);
	}
	free(base);
	return (str);
}

static void	banker_round(long double nbr, char *dl_str, long *base, size_t len)
{
	if (nbr > 0.5f)
	{
		if (dl_str[len] == '9')
		{
			while (dl_str[len] == '9')
				dl_str[len--] = '0';
			if (dl_str[len] == '.')
				base[0]++;
			else
				dl_str[len]++;
		}
		else
			dl_str[len]++;
	}
	if (nbr == 0.5f && dl_str[len] == '0')
		dl_str[len]++;
}

static char	*precision_zero(long double nbr, long *base_l)
{
	if (nbr > 0.5f)
		base_l[0]++;
	else if (nbr == 0.5f)
		if ((base_l[0] % 2) != 0)
			base_l[0]++;
	return (ft_strdup(""));
}

static char	*remain(long double nbr, size_t precision, long *base_l)
{
	char	*ret;
	char	*tmp;
	long	base;
	int		index;

	tmp = NULL;
	if (precision == 0)
		return (precision_zero(nbr, base_l));
	ret = (char *)ft_memalloc(precision + 1);
	index = 0;
	ret[precision] = '\0';
	while (precision--)
	{
		nbr *= 10;
		base = ((long)nbr);
		ret[index++] = (base % 10) + '0';
		nbr -= (long double)base;
	}
	tmp = ret;
	ret = ft_strjoin(".", ret);
	free(tmp);
	banker_round(nbr, ret, base_l, (ft_strlen(ret) - 1));
	return (ret);
}

/**
 * It takes a long double,
 * converts it to a string, and returns the string
 * 
 * @param nbr the number to be converted
 * @param precision the number of decimal places to round to
 * 
 * @return A string containing the float value of the long double passed in.
 */
char	*ft_lftoa(long double nbr, size_t precision)
{
	char	*ret;
	char	*sign;
	long	*base;

	ret = NULL;
	sign = NULL;
	if (nbr == 1.0 / 0.0)
		return (ft_strdup("inf"));
	if (nbr == -1.0 / 0.0)
		return (ft_strdup("-inf"));
	if (nbr != nbr)
		return (ft_strdup("nan"));
	base = (long *)malloc(sizeof(long));
	if (!base)
		ft_exit_no_mem(1);
	if (1 / nbr < 0)
	{
		sign = ft_strdup("-");
		nbr *= -1;
	}
	*base = (long)nbr;
	nbr -= (long double)base[0];
	ret = remain(nbr, precision, base);
	ret = joiner(sign, ret, base);
	return (ret);
}
