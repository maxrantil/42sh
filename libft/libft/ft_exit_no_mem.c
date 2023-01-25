/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_no_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:28:16 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/17 17:54:28 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Ft_exit_no_mem() is a function that prints a message to the standard output
 * and exits the program with a status of 1.
 * 
 * @param status The exit status.
 */
void	ft_exit_no_mem(int status)
{
	ft_putstr("No Memory Available: Exit\n");
	exit(status);
}
