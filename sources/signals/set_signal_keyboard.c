/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_keyboard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:34:34 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/11 18:03:12 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It sets the signal handler for all signals to the function ft_signal_keyboard
 */
void	set_signal_keyboard(void)
{
	int	sig;

	sig = 0;
	while (++sig < 32)
	{
		if (sig == SIGCHLD)
			signal(sig, handler_sigchild);
		else if (sig == SIGTTIN)
			signal(sig, SIG_IGN);
		else if (sig == SIGTTOU)
			signal(sig, SIG_IGN);
		else
			signal(sig, ft_signal_keyboard);
	}
}
