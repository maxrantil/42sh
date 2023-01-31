/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_keyboard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:34:34 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/30 16:05:06 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It sets the signal handler for all signals to the function ft_signal_keyboard
 */
void	set_signal_keyboard(void)
{
	int	sig;

	sig = -1;
	while (++sig < 32)
		signal(sig, ft_signal_keyboard);
	signal(SIGCHLD, child_exit);
}
