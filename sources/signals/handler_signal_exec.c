/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:06:21 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/01 12:41:47 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

void	signal_exec(int num)
{
	struct winsize	size;

	if (num == SIGWINCH)
	{
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < -1)
		{
			ft_putstr_fd("could not get the terminal size", 1);
			exit(0);
		}
		g_sh->term->ws_col = size.ws_col;
		g_sh->term->ws_row = size.ws_row;
	}
	// if (num == SIGSTOP || num == SIGTSTP)
	// 	kill(g_sh->fg_node->gpid, SIGSTOP);
}
