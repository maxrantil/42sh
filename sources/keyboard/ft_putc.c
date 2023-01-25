/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:19:49 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 16:49:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It writes a single character to the standard output.
 *
 * @param c The character to print.
 *
 * @return The number of bytes written.
 */
int	ft_putc(int c)
{
	return ((int)write(1, &c, 1));
}
