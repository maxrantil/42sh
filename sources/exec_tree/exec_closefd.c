/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_closefd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:13:40 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/23 02:43:36 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	exec_closefd(t_closefd *node, char ***environ_cp, \
char *terminal, t_shell *sh)
{
	if(sh->pipe->previous_redir[node->close_fd] != 1)
		close(node->close_fd);
	if (node->close_fd == STDOUT_FILENO)
	{
		close(sh->pipe->write_pipe[1]);
		close(sh->pipe->read_pipe[1]);
		sh->pipe->read_pipe[1] = -1;
		sh->pipe->write_pipe[1] = -1;
	}
	if (node->cmd)
		exec_tree(node->cmd, environ_cp, terminal, sh);
	if (sh->pipe->piping && node->close_fd == STDOUT_FILENO)
	{
		if (dup2(sh->pipe->stdincpy, STDOUT_FILENO) < 0)
			error_exit("dup2 failed in exec_closefd");
	}
}
