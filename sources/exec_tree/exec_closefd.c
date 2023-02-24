
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_closefd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:13:40 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/23 10:29:28 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	exec_closefd(t_closefd *node, char ***environ_cp, \
char *terminal, t_shell *sh)
{
	if (!sh->pipe->redir_fork)
	{
		sh->pipe->redir_fork = 1;
		sh->pipe->pid = fork_wrap();
		if (sh->pipe->pid != 0)
		{
			sh->pipe->redir_fork = 0;
			// set_process_group(sh, sh->pipe->pid);
			update_fg_job(sh, sh->pipe->pid, ((t_cmdnode *)node->cmd)->cmd);
			wait_for_job(sh, sh->pipe->pid);
		}
	}
	if (sh->pipe->pid == 0)
	{
		if (sh->pipe->previous_redir[node->close_fd] != 1)
			close(node->close_fd);
		sh->pipe->closed_fds[node->close_fd] = 1;
		if (node->close_fd == STDOUT_FILENO)
		{
			sh->pipe->close_fd = STDOUT_FILENO;
			close(sh->pipe->write_pipe[1]);
			close(sh->pipe->read_pipe[1]);
			sh->pipe->read_pipe[1] = -1;
			sh->pipe->write_pipe[1] = -1;
		}
		if (node->cmd)
			exec_tree(node->cmd, environ_cp, terminal, sh);
		if (node->close_fd == STDOUT_FILENO)
		{
			if (dup2(sh->pipe->stdincpy, STDOUT_FILENO) < 0)
				error_exit("dup2 failed in exec_closefd");
		}
	}
}
