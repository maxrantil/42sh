/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_ign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:03:12 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/01 12:27:51 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It sets all signals to be ignored
 */
void	ft_signal_ign(void)
{
	int	sig;

	sig = 1;
	while (sig < 32)
		signal(sig++, SIG_IGN);
	signal(SIGCHLD, handler_sigchild);
}
