/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_closefd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:13:40 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/22 11:37:28 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	exec_closefd(t_closefd *node, char ***environ_cp, \
char *terminal, t_shell *sh)
{
	if (!close_fd_alias_if_necessary(sh, node->close_fd))
		close(node->close_fd);
	if (node->cmd && node->cmd->type == CMD)
		sh->pipe->redir_out = 1;
	if (sh->pipe->write_pipe[1] > 0)
	{
		close(sh->pipe->write_pipe[1]);
		sh->pipe->write_pipe[1] = -1;
	}
	if (node->cmd)
		exec_tree(node->cmd, environ_cp, terminal, sh);
	reset_fd(sh); // MAYBE DO SIMILAR THAN OTHER REDIRS INSTEAD
	// close(STDIN_FILENO);
	// close(STDOUT_FILENO);
	// open(sh->terminal, O_RDWR);
	// open(sh->terminal, O_RDWR);
}
