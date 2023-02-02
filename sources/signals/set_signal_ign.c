/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_ign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:36:35 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/02 21:11:40 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

static void	update_window_size(int num)
{
	struct winsize	size;

	if (num == SIGWINCH)
	{
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0)
		{
			ft_putstr_fd("could not get the terminal size", 2);
			ft_raw_disable(g_sh->orig_termios);
			exit(1);
		}
		g_sh->term->ws_col = size.ws_col;
		g_sh->term->ws_row = size.ws_row;
	}
}

void set_signal_ign(void)
{
	int sig;

	sig = 0;
	while (++sig < 32)
	{
		if (sig == SIGCHLD)	
			continue;
		else if (sig == SIGWINCH)
			signal(SIGWINCH, update_window_size);
		else
			signal(sig, SIG_IGN);
	}
}
