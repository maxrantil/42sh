/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal_search_history.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:04:37 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/06 12:17:07 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

void	search_history_sigs(int num)
{
	struct winsize	size;
	t_term			*term;

	term = g_sh->term;
	if (num == SIGWINCH)
	{
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < -2)
		{
			ft_putstr_fd("could not get the terminal size", 0);
			exit(1);
			// ft_exit(g_sh, -1);
		}
		term->ws_col = size.ws_col;
		term->ws_row = size.ws_row;
		ft_search_history_reset(term);
	}
	if (num == SIGINT)
	{
		ft_setcursor(0, (term->term_val[1]-- + term->total_row));
		ft_run_capability("cd");
		ft_restart_cycle(term);
		term->config->status = 0;
		ft_memdel((void **)&term->config->ptr);
	}
}
