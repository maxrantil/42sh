/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:23:35 by jakken            #+#    #+#             */
/*   Updated: 2023/02/06 11:14:28 by mbarutel         ###   ########.fr       */
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
		reset_fd(terminal);
		if (head && ((t_semicolon *)head)->right)
			exec_tree((((t_semicolon *)head)->right), environ_cp, terminal, sh);
		reset_fd(terminal);
	}
	else if (head->type == PIPE)
		exec_pipe((t_pipenode *)head, environ_cp, terminal, sh);
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
		// ft_printf("hello\n");
		transfer_to_bg(sh, RUNNING);
		// ft_printf("bye\n");
		reset_fgnode(sh);
		display_bg_job(sh);
		sh->ampersand = false;
		reset_fd(terminal);
		exec_tree((((t_ampersand *)head)->right), environ_cp, terminal, sh);
		reset_fd(terminal);
	}
}
