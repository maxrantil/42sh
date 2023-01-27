/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_keyboard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:34:34 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/27 15:02:54 by mbarutel         ###   ########.fr       */
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
}
