/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_if_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 01:10:27 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/25 01:16:56 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	dup_the_dups(t_shell *sh)
{
	if (sh->pipe->close_fd < 0)
	{
		if (dup2(sh->pipe->stdincpy, STDOUT_FILENO) < 0)
		{
			ft_err_print("dup2", NULL, "failed", 2);
			exit(1);
		}
	}
	if (sh->pipe->close_fd != STDOUT_FILENO && sh->pipe->write_pipe[1] >= 0 \
	&& dup2(sh->pipe->write_pipe[1], STDOUT_FILENO) < 0)
	{
		ft_err_print("dup2", NULL, "failed", 2);
		exit(1);
	}
}

int	fork_if_pipe(t_shell *sh, char ***cmd, char ***environ_cp)
{
	int	pid;

	if (sh->pipe->piping || sh->ampersand)
	{
		if (sh->pipe->redir_fork == 0)
			sh->pipe->pid = fork_wrap();
		pid = sh->pipe->pid;
		if (sh->pipe->pid == 0)
			sh->pipe->pid = pid;
		if (pid)
			update_fg_job(sh, pid, *cmd);
		if (pid == 0)
		{
			ft_signal_dfl();
			dup_the_dups(sh);
			cmd_comparisons(sh, cmd, environ_cp);
			exit(1);
		}
		return (1);
	}
	return (0);
}
