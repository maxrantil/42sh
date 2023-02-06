/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_search_history.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:33:56 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/02 17:00:02 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	set_signal_search_history(void)
{
	int	sig;

	sig = 0;
	while (++sig < 32)
	{
		if (sig == SIGCHLD)
			continue ;
		else if (sig == SIGTTIN)
			signal(sig, SIG_IGN);
		else if (sig == SIGTTOU)
			signal(sig, SIG_IGN);
		else
			signal(sig, search_history_sigs);
	}
}
