/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_dfl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:25:14 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/01 12:17:18 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It sets all the signals to their default behavior
 */
void	ft_signal_dfl(void)
{
	int	sig;

	sig = 1;
	while (sig < 32)
		signal(sig++, SIG_DFL);
	signal(SIGCHLD, SIG_IGN);
}
