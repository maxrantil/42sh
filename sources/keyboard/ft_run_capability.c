/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_capability.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:41:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 16:52:42 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It takes a capability name as a string, and runs the capability
 *
 * @param cap The capability name.
 */
void	ft_run_capability(char *cap)
{
	char	*p;

	p = tgetstr(cap, NULL);
	if (p == NULL)
	{
		ft_putstr_fd("error: ", 2);
		ft_putstr_fd(cap, 2);
		ft_putstr_fd(" : cannot ft_run_capability()\n", 2);
	}
	else
		tputs(p, 1, ft_putc);
}
