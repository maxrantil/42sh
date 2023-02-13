/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:23:35 by jakken            #+#    #+#             */
/*   Updated: 2023/02/13 12:54:36 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	exec_tree(t_treenode *head, char ***environ_cp,
				char *terminal, t_shell *sh)
{
	if (!head)
		return ;
	if (head->type == SEMICOLON)
	{
		exec_tree((((t_semicolon *)head)->left), environ_cp, terminal, sh);

		sh->pipe->redir_in = 0;
		sh->pipe->redir_out = 0;
		reset_fd(terminal); // Always redup after reset_fd
		sh->pipe->stdincpy = dup(STDIN_FILENO);
		sh->pipe->stdoutcpy = dup(STDOUT_FILENO);
		if (head && ((t_semicolon *)head)->right)
			exec_tree((((t_semicolon *)head)->right), environ_cp, terminal, sh);
		reset_fd(terminal);
		sh->pipe->stdincpy = dup(STDIN_FILENO);
		sh->pipe->stdoutcpy = dup(STDOUT_FILENO);
		sh->pipe->redir_in = 0;
		sh->pipe->redir_out = 0;
	}
	else if (head->type == PIPE)
	{
		sh->pipe->piping = 1;
		exec_pipe((t_pipenode *)head, environ_cp, terminal, sh);
	}
	else if (head->type == REDIR)
		exec_redir((t_redir *)head, environ_cp, terminal, sh);
	else if (head->type == AGGREGATION)
		exec_aggregate((t_aggregate *)head, environ_cp, terminal, sh);
	else if (head->type == CLOSEFD)
		exec_closefd((t_closefd *)head, environ_cp, terminal, sh);
	else if (head->type == CMD)
		exec_cmd(((t_cmdnode *)head), environ_cp, sh);
	else if (head->type == LOGICAL_AND || head->type == LOGICAL_OR)
		exec_logicalop(((t_logicalop *)head), environ_cp, terminal, sh);
	else if (head->type == AMPERSAND)
	{
		sh->ampersand = true;
		exec_tree((((t_ampersand *)head)->left), environ_cp, terminal, sh);
		transfer_to_bg(sh, RUNNING);
		display_bg_job(sh);
		reset_fgnode(sh);
		// ft_printf("stdout: %d\n", sh->pipe->stdoutcpy);
		sh->ampersand = false;
		reset_fd(terminal);
		exec_tree((((t_ampersand *)head)->right), environ_cp, terminal, sh);
		reset_fd(terminal);
	}

}
