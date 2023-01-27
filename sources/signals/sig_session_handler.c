/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_session_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:02:29 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/26 13:16:34 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

/*
 * It's a signal handler that
 * handles the window size change and the interrupt signal
 *
 * @param num The signal number.
 */
void	sig_session_handler(int num)
{
	if (num == SIGWINCH)
		ft_window_size(g_sh->term);
	if (num == SIGINT)
		ft_restart_cycle(g_sh->term);
}

void	sigwinch_inchild_handler(int num)
{
	struct winsize	size;

	if (num == SIGWINCH)
	{
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0)
		{
			ft_putstr_fd("could not get the terminal size", 2);
			exit(1);
		}
		g_sh->term->ws_col = size.ws_col;
		g_sh->term->ws_row = size.ws_row;
	}
}

void	search_history_sigs(int num)
{
	struct winsize	size;
	t_term			*term;

	term = g_sh->term;
	if (num == SIGWINCH)
	{
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0)
		{
			ft_putstr_fd("could not get the terminal size", 2);
			exit(1);
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
