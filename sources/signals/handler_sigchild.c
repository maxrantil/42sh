/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sigchild.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:13:55 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/06 22:23:27 by jniemine         ###   ########.fr       */
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

static void    change_process_status(t_bg_jobs *bg_node, pid_t pid, int status)
{
    t_bg_jobs    *job;

    job = bg_node;
    while (job && job->gpid != pid)
        job = job->next;
	if (job)
		job->status = status;
}

static void	check_pipeline(t_shell *sh, pid_t pid)
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
			g_sh->pipe->redir_out = 0;
			reset_fd(g_sh->terminal);
			close(g_sh->pipe->pipefd[0]);
			close(g_sh->pipe->pipefd[1]);
			g_sh->pipe->pipefd[0] = -1;
			g_sh->pipe->pipefd[1] = -1;
		}
		if (pid > 0) // this means that the process is exited, via completion or termination
		{
			check_pipeline(g_sh, pid);
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
			exit_error(g_sh, 1, "ioctl error in handler_sigchild()");
	}
}
