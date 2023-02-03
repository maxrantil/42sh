/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sigchild.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:13:55 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/03 13:23:06 by mbarutel         ###   ########.fr       */
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
	if (job)
		job->status = status;
}

void handler_sigchild(int num)
{
	int		status;
	pid_t	pid;

	if (num == SIGCHLD)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (pid > 0) // this means that the process is exited, via completion or termination
		{
			if (g_sh->fg_node->gpid && g_sh->fg_node->gpid == pid)
				reset_fgnode(g_sh);
			change_process_status(g_sh->bg_node, pid, DONE);
			if (WIFSIGNALED(status))
				ft_putchar('\n');
		}
		else //if suspended it goes here
		{
			transfer_to_bg(g_sh, STOPPED);
			reset_fgnode(g_sh);
			display_suspended_job(g_sh);
		}
		set_signal_keyboard();
		if (ioctl(STDIN_FILENO, TIOCSPGRP, &g_sh->pgid) == -1)
			ft_exit(g_sh, 1); // this needs to be proper exit
	}
}
