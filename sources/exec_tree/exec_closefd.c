/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_closefd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:13:40 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/25 00:58:48 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	fork_if_needed(t_closefd *node, t_shell *sh)
{
	int			builtin;
	char		**cmd;

	builtin = 0;
	cmd = get_cmd_name((t_treenode *)node);
	builtin = is_builtin(cmd);
	if (!sh->pipe->redir_fork && !builtin)
	{
		sh->pipe->redir_fork = 1;
		sh->pipe->pid = fork_wrap();
		if (sh->pipe->pid != 0)
		{
			sh->pipe->redir_fork = 0;
			update_fg_job(sh, sh->pipe->pid, get_cmd_name((t_treenode *)node));
			wait_for_job(sh, sh->pipe->pid);
		}
	}
	return (builtin);
}

static void	close_pipes(t_shell *sh)
{
	sh->pipe->close_fd = STDOUT_FILENO;
	close(sh->pipe->write_pipe[1]);
	close(sh->pipe->read_pipe[1]);
	sh->pipe->read_pipe[1] = -1;
	sh->pipe->write_pipe[1] = -1;
}

void	exec_closefd(t_closefd *node, char ***environ_cp, \
char *terminal, t_shell *sh)
{
	int	builtin;

	builtin = fork_if_needed(node, sh);
	if (sh->pipe->pid == 0 || builtin)
	{
		if (!builtin)
			ft_signal_dfl();
		if (sh->pipe->previous_redir[node->close_fd] != 1)
			close(node->close_fd);
		sh->pipe->closed_fds[node->close_fd] = 1;
		if (node->close_fd == STDOUT_FILENO)
			close_pipes(sh);
		if (node->cmd)
			exec_tree(node->cmd, environ_cp, terminal, sh);
		if (node->close_fd == STDOUT_FILENO)
		{
			if (dup2(sh->pipe->stdincpy, STDOUT_FILENO) < 0)
				error_exit("dup2 failed in exec_closefd");
		}
	}
}
