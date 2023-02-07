/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sigchild.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:13:55 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/07 11:10:39 by mbarutel         ###   ########.fr       */
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

// static bool	check_bg_pipeline(t_bg_jobs *job, pid_t pid)
// {
// 	pid_t	*ptr;

// 	ptr = job->pid;
// 	while (*ptr)
// 	{
// 		if (*ptr == pid)
// 			return (true);
// 		ptr++;
// 	}
// 	return (false);
// }

// static void    change_process_status(t_bg_jobs *bg_node, pid_t pid, int status)
// {
//     t_bg_jobs    *job;

//     job = bg_node;
//     while (job)
// 	{
// 		if (check_bg_pipeline(job, pid))
// 			break ;	
//         job = job->next;
// 	}
// 	if (job)
// 		job->status = status;
// }

// static void	check_fg_pipeline(t_shell *sh, pid_t pid)
// {
// 	pid_t	*ptr;

// 	if (!sh->fg_node->gpid)
// 		return ;
// 	ptr = sh->fg_node->pid;
// 	while (*ptr)
// 	{
// 		if (*ptr == pid)
// 		{
// 			reset_fgnode(sh);
// 			return ;
// 		}
// 		ptr++;
// 	}
// }

static void	reset_pipes(t_shell *sh)
{
	if (sh->pipe->pipefd[0] > -1 || sh->pipe->pipefd[1] > -1)
	{
		sh->pipe->redirecting = 0;
		reset_fd(sh->terminal);
		close(sh->pipe->pipefd[0]);
		close(sh->pipe->pipefd[1]);
		sh->pipe->pipefd[0] = -1;
		sh->pipe->pipefd[1] = -1;
	}
}

// void handler_sigchild(int num)
// {
// 	int		status;
// 	pid_t	pid;

// 	if (num == SIGCHLD)
// 	{
// 		pid = waitpid(-1, &status, WNOHANG);
// 		reset_pipes(g_sh);			
// 		if (pid > 0) // this means that the process is exited, via completion or termination
// 		{
// 			check_fg_pipeline(g_sh, pid);
// 			if (WIFSIGNALED(status))
// 			{
// 				ft_putchar('\n');
// 				if (WTERMSIG(status))
// 					change_process_status(g_sh->bg_node, pid, TERMINATED);
// 			}
// 			else
// 				change_process_status(g_sh->bg_node, pid, DONE);
// 		}
// 		else //if suspended it goes here
// 		{
// 			ft_putchar('\n');
// 			transfer_to_bg(g_sh, STOPPED);
// 			display_suspended_job(g_sh);
// 			reset_fgnode(g_sh);
// 		}
// 		if (ioctl(STDIN_FILENO, TIOCSPGRP, &g_sh->pgid) == -1)
// 			ft_exit(g_sh, 1);
// 	}
// }

void handler_sigchild(int num)
{
	// int		status;
	// pid_t	pid;

	if (num == SIGCHLD)
	{
		reset_pipes(g_sh);		
		// ft_printf("SIGCHILD signal recieved\n");
		// pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
		// while (pid > 0)
		// {
		// 	ft_printf("pid %d\n", pid);
		// 	if (WIFSIGNALED(status)) // This is for when a process has been signalled
		// 	{
		// 		ft_putchar('\n');
		// 		ft_printf("terminated\n");
		// 		// if (WTERMSIG(status)) // This is for when the signal is termination
		// 		// 	change_process_status(g_sh->bg_node, pid, TERMINATED);
		// 	}
		// 	else if (WIFSTOPPED(status)) // This is for when the process has been suspended and can still continue
		// 	{
		// 		ft_putchar('\n');
		// 		ft_printf("suspended\n");
		// 		// transfer_to_bg(g_sh, STOPPED);
		// 		// display_suspended_job(g_sh);
		// 		// reset_fgnode(g_sh);
		// 	}
		// 	else if (WIFEXITED(status)) // This is for when the process has exited without interruption
		// 	{
		// 		ft_printf("exited\n");
		// 		// change_process_status(g_sh->bg_node, pid, DONE);
		// 	}
		// 	pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
		// 	ft_printf("continue? %d\n", pid);
		// }
		// ft_printf("Ending\n");
		if (ioctl(STDIN_FILENO, TIOCSPGRP, &g_sh->pgid) == -1)
			ft_exit(g_sh, 1);
		// ft_printf("Ending here\n");
	}
}

