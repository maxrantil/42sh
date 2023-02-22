/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_print_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:10:35 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/22 11:42:57 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	ft_history_print_error(char *str, int prefix)
{
	ft_putstr_fd("\n42sh: !", 2);
	if (prefix == 2)
		ft_putstr_fd("-", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": event not found", 2);
	return (0);
}
