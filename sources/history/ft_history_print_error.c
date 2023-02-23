/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_print_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:10:35 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/23 14:27:33 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

int	ft_history_print_error(char *str, int prefix)
{
	g_sh->term->total_row++;
	ft_putstr_fd("\n42sh: !", 2);
	if (prefix == 2)
		ft_putstr_fd("-", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": event not found", 2);
	return (0);
}
