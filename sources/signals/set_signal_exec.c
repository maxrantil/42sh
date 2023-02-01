/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:24:56 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/01 12:28:36 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	set_signal_exec(void)
{
	int	sig;

	sig = -1;
	while (++sig < 32)
		signal(sig, signal_exec);
	signal(SIGCHLD, handler_sigchild);
}
