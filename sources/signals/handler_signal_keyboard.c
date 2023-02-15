/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_keyboard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:02:29 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/26 21:06:48 by mbarutel         ###   ########.fr       */
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
void	ft_signal_keyboard(int num)
{
	if (num == SIGWINCH)
		ft_window_size(g_sh->term);
	if (num == SIGINT)
		ft_restart_cycle(g_sh->term);
	if (num == SIGSEGV)
	{
		ft_putendl_fd("Segmentation fault: 11", 2);
		ft_history_write_to_file(g_sh->term);
		ft_raw_disable(g_sh->orig_termios);
		exit(num);
	}
}
