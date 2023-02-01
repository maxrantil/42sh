/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sigchild.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:13:55 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/01 18:46:53 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

static void    change_process_status(t_bg_jobs *bg_node, pid_t pid, int status)
{
    t_bg_jobs    *job;

    job = bg_node;
    while (job && job->gpid != pid)
        job = job->next;
    job->status = status;
}

void handler_sigchild(int num)
{
	int		status;
	pid_t	pid;

	if (num == SIGCHLD)
	{
		set_signal_keyboard();
		if (ioctl(STDIN_FILENO, TIOCSPGRP, &g_sh->pgid) == -1)
		{
			ft_printf("error here\n");
			exit (1); // this needs to be proper exit
		}
		pid = waitpid(-1, &status, WNOHANG);
		if (pid > 0) // this means that the process is exited, via completion or termination
		{
			ft_printf("PROCESS COMPLETED\n");
			change_process_status(g_sh->bg_node, pid, DONE);
		}
		else //if suspended it goes here
		{
			transfer_to_bg(g_sh, SUSPENDED);
			reset_fgnode(g_sh);
			ft_printf("PROCESS SUSPENDED\n");
		}
		// print_fg_node(g_sh);
		// transfer fg struct to a bg node along the list
		// reset the fg node
	}
}
