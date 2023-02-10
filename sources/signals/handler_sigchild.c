/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sigchild.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:13:55 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/10 14:45:56 by jniemine         ###   ########.fr       */
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
	char	***cmd;

	if (!sh->fg_node->gpid)
		return ;
	ptr = sh->fg_node->pid;
	cmd = sh->fg_node->cmd;
	while (ptr && *ptr)
	{
		if (*ptr == pid)
		{
			ft_putstr_fd("RESET FG NODE\n", 2);
			ft_putstr_fd(**cmd, 2);
			ft_putstr_fd(*(*cmd + 1), 2);
			reset_fgnode(sh);
			return ;
		}
		cmd++;
		ptr++;
	}
}

// static void	reset_pipes(t_shell *sh)
// {
// 	if (sh->pipe->write_pipe[0] > -1 || sh->pipe->write_pipe[1] > -1)
// 	{
// 		sh->pipe->redir_out = 0;
// 		sh->pipe->redir_in = 0;
// 		reset_fd(sh->terminal);
// 		// close(sh->pipe->write_pipe[0]);
// 		close(sh->pipe->write_pipe[1]);
// 		// sh->pipe->write_pipe[0] = -1;
// 		sh->pipe->write_pipe[1] = -1;
// 	}
// }

#include <errno.h>
 #include <stdio.h>
void	handler_sigchild(int num)
{
	int		status;
	pid_t	pid;

	if (num == SIGCHLD)
	{
		pid = waitpid(-1, &status, WNOHANG);

		if (pid > 0) // this means that the process is exited, via completion or termination
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status))
				{
					check_fg_pipeline(g_sh, pid);
					change_process_status(g_sh->bg_node, pid, TERMINATED);
				}
			}
			else
				change_process_status(g_sh->bg_node, pid, DONE);
		}
		else //if suspended it goes here
		{
			ft_putchar('\n');
			--g_sh->process_count;
			transfer_to_bg(g_sh, STOPPED);
			// display_suspended_job(g_sh);
			reset_fgnode(g_sh);
		}
		}

}
