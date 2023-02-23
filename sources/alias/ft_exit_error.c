/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:06:05 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/23 15:07:05 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	ft_exit_error(char *msg, int ret)
{
	ft_putstr_fd("FATAL error in \"", 2);
	ft_putstr_fd((const char *)msg, 2);
	ft_putstr_fd("\" -> exit(", 2);
	ft_putnbr_fd(ret, 2);
	ft_putstr_fd(")\n", 2);
	exit(ret);
}
