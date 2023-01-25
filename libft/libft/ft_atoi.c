/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:01:41 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/03 21:17:48 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * It takes a string, and returns an integer
 * 
 * @param nbr The string to be converted to an integer.
 * 
 * @return the integer value of the string passed as argument.
 */
int	ft_atoi(const char *nbr)
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
	if (result > 9223372036854775807UL && sign == 1)
		return (-1);
	if (result > 9223372036854775808UL && sign == -1)
		return (0);
	return ((int)(result * sign));
}
