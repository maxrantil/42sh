/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_closefd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:13:40 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/01 21:58:41 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	exec_closefd(t_closefd *node, char ***environ_cp,
		char *terminal, t_shell *sh)
{
	close(node->close_fd);
	if (node->cmd && node->cmd->type == CMD)
		((t_cmdnode *)node->cmd)->redirecting = 1;
	if (node->cmd)
		exec_tree(node->cmd, environ_cp, terminal, sh);
	reset_fd(sh->terminal);
}
