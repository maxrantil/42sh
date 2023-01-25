/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:07:06 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/05 12:34:14 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_putstr() writes the string s to the standard output
 * 
 * @param s The string to be printed.
 */
void	ft_putstr(char const *s)
{
	write(1, s, ft_strlen(s));
}
