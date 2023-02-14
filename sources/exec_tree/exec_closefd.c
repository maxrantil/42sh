/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_closefd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:13:40 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/14 15:45:05 by mbarutel         ###   ########.fr       */
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
}
