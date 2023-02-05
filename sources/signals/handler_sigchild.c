/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sigchild.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:13:55 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/05 14:22:24 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

// static int	print_fg_node(t_shell *sh)
// {
// 	pid_t	*tmp;
// 	char	***ptr;
// 	char	**dbl;

// 	tmp = sh->fg_node->pid;
// 	while (tmp && *tmp)
// 		ft_printf("pid: %d\n", *(tmp++));
// 	ptr = sh->fg_node->cmd;
// 	while (ptr && *ptr)
// 	{
// 		dbl = *ptr;
// 		while (*dbl)
//         {
// 			ft_printf("cmd: %s\n", *dbl);
//             dbl++;
//         }
//         ptr++;
// 	}
// 	return (0);
// }

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

static void    change_process_status(t_bg_jobs *bg_node, pid_t pid, int status)
{
    t_bg_jobs    *job;

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

void handler_sigchild(int num)
{
	int		status;
	pid_t	pid;

	if (num == SIGCHLD)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (g_sh->pipe->pipefd[0] > -1 || g_sh->pipe->pipefd[1] > -1)
		{
			g_sh->pipe->redirecting = 0;
			reset_fd(g_sh->terminal);
			close(g_sh->pipe->pipefd[0]);
			close(g_sh->pipe->pipefd[1]);
			g_sh->pipe->pipefd[0] = -1;
			g_sh->pipe->pipefd[1] = -1;
		}
		if (pid > 0) // this means that the process is exited, via completion or termination
		{
			check_fg_pipeline(g_sh, pid);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status))
					change_process_status(g_sh->bg_node, pid, TERMINATED);
			}
			else
				change_process_status(g_sh->bg_node, pid, DONE);
		}
		else //if suspended it goes here
		{
			transfer_to_bg(g_sh, STOPPED);
			reset_fgnode(g_sh);
			ft_putchar('\n');
			display_suspended_job(g_sh);
		}
		set_signal_keyboard();
		if (ioctl(STDIN_FILENO, TIOCSPGRP, &g_sh->pgid) == -1)
			ft_exit(g_sh, 1);
	}
}
