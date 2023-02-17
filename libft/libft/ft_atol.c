/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:28:51 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/17 17:15:09 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nbr)
{
	unsigned int	index;
	unsigned long	result;
	long			sign;

	index = 0;
	result = 0;
	sign = 1;
	while (nbr[index] == ' ' || (nbr[index] >= 9 && nbr[index] <= 13))
		index++;
	if (nbr[index] == '-' || nbr[index] == '+')
	{
		if (nbr[index] == '-')
			sign = -1;
		index++;
	}
	while (nbr[index] != '\0' && ((nbr[index] >= '0' && nbr[index] <= '9')))
	{
		result = result * 10 + nbr[index] - '0';
		index++;
	}
	if (result > LONG_MAX && sign == 1)
		return (-1);
	if (result >= LONG_MAX && sign == -1)
		return (0);
	return ((result * sign));
}
