/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:08:30 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/14 12:30:54 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Iterate through the string and apply the function to each character
 * 
 * @param str The string to iterate through.
 * @param f a function that takes a char pointer as a parameter and returns
 * nothing.
 */
void	ft_striter(char *str, void (*f)(char *))
{
	int	i;

	i = 0;
	if (str && f)
	{
		while (str[i] != '\0')
		{
			f(&str[i]);
			i++;
		}
	}
}
