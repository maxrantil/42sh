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


# include <stdio.h> //DELT
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
}

void child_exit(int num)
{
    int        status;
    pid_t    pid;

    if (num == SIGCHLD)
    {
        // ft_printf("pid: %d\n", pid);
        pid = waitpid(-1, &status, WNOHANG);
        if (pid > 0) // this means that the process is exited, via completion or termination
        {
			fflush(stdout);
			// ft_printf("PROCESS FINISHED, PID: %d||\n", pid);
			ft_putstr_fd("PROCESS FINISHED PID: ", 2);
			ft_putnbr_fd(pid, 2);
			ft_putstr_fd("\n", 2);
			fflush(stdout);
        }
        else //if suspended it goes here
        {
			// ft_putstr("PROCESS SUSPENDED");
			ft_putstr_fd("PROCESS SUSPENDED\n", 2);
        }
    }
}



