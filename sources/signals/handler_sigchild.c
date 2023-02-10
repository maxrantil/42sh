/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sigchild.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:13:55 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/10 17:40:19 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

static bool	check_bg_pipeline(t_bg_jobs *job, pid_t pid)
{
	pid_t	*ptr;

	ptr = job->pid;
	while (*ptr)
	{
		if (*ptr == pid)
			return (true);
		ptr++;
	}
	return (false);
}

static void	change_process_status(t_bg_jobs *bg_node, pid_t pid, int status)
{
	t_bg_jobs	*job;

	job = bg_node;
	while (job)
	{
		if (check_bg_pipeline(job, pid))
			break ;
		job = job->next;
	}
	if (job)
		job->status = status;
}

static void	check_fg_pipeline(t_shell *sh, pid_t pid)
{
	pid_t	*ptr;

	if (!sh->fg_node->gpid)
		return ;
	ptr = sh->fg_node->pid;
	while (*ptr)
	{
		if (*ptr == pid)
		{
			reset_fgnode(sh);
			return ;
		}
		ptr++;
	}
}

void	handler_sigchild(int num)
{
	int		status;
	pid_t	pid;

	if (num == SIGCHLD)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (pid > 0) // this means that the process is exited, via completion or termination
		{
			check_fg_pipeline(g_sh, pid);
			if (WIFSIGNALED(status))
			{
				ft_putchar('\n');
				if (WTERMSIG(status))
					change_process_status(g_sh->bg_node, pid, TERMINATED);
			}
			else
				change_process_status(g_sh->bg_node, pid, DONE);
		}
		else //if suspended it goes here
		{
			ft_putchar('\n');
			--g_sh->process_count;
			transfer_to_bg(g_sh, STOPPED);
			display_suspended_job(g_sh);
			reset_fgnode(g_sh);
		}
		if (ioctl(STDIN_FILENO, TIOCSPGRP, &g_sh->pgid) == -1)
			exit_error(g_sh, 1, "ioctl error in handler_sigchild()");
	}
}
