/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:23:35 by jakken            #+#    #+#             */
/*   Updated: 2023/01/25 16:20:57 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_21sh.h"

/* static void	free_rest(t_treenode *head)
{
	if (head->type == CMD)
	{
		ft_freeda((void ***)&((t_cmdnode *)head)->cmd,
			calc_chptr(((t_cmdnode *)head)->cmd));
	}
	else if (head->type == REDIR)
	{
		free_node(((t_redir *)head)->cmd);
		ft_memdel((void **)&(((t_redir *)head)->filepath));
	}
	else if (head->type == CLOSEFD)
		free_node(((t_redir *)head)->cmd);
	else if (head->type == AGGREGATION)
	{
		ft_strdel(&((t_aggregate *)head)->dest);
		free_node(((t_aggregate *)head)->cmd);
	}
	else if (head->type == AMPERSAND)
	{
		free_node(((t_ampersand *)head)->left);
		((t_semicolon *)head)->left = NULL;
		free_node(((t_ampersand *)head)->right);
		((t_semicolon *)head)->right = NULL;
	}
	ft_memdel((void **)&head);
} */

/* void	free_node(t_treenode *head)
{
	if (!head)
		return ;
	if (head->type == SEMICOLON)
	{
		free_node(((t_semicolon *)head)->left);
		((t_semicolon *)head)->left = NULL;
		free_node(((t_semicolon *)head)->right);
		((t_semicolon *)head)->right = NULL;
	}
	else if (head->type == PIPE)
	{
		free_node(((t_pipenode *)head)->left);
		((t_pipenode *)head)->left = NULL;
		free_node(((t_pipenode *)head)->right);
		((t_pipenode *)head)->right = NULL;
	}
	else if (head->type == LOGICAL_AND || head->type == LOGICAL_OR)
	{
		free_node(((t_logicalop *)head)->left);
		((t_logicalop *)head)->left = NULL;
		free_node(((t_logicalop *)head)->right);
		((t_logicalop *)head)->right = NULL;
	}
	free_rest(head);
} */

void	exec_tree(t_treenode *head, char ***environ_cp,
				char *terminal, t_session *sesh)
{
	if (!head)
		return ;
	if (head->type == SEMICOLON)
	{
		exec_tree((((t_semicolon *)head)->left), environ_cp, terminal, sesh);
		reset_fd(terminal);
		if (head && ((t_semicolon *)head)->right)
			exec_tree((((t_semicolon *)head)->right), environ_cp, terminal, sesh);
		reset_fd(terminal);
	}
	else if (head->type == PIPE)
		exec_pipe((t_pipenode *)head, environ_cp, terminal, sesh);
	else if (head->type == REDIR)
		exec_redir((t_redir *)head, environ_cp, terminal, sesh);
	else if (head->type == AGGREGATION)
		exec_aggregate((t_aggregate *)head, environ_cp, terminal, sesh);
	else if (head->type == CLOSEFD)
		exec_closefd((t_closefd *)head, environ_cp, terminal, sesh);
	else if (head->type == CMD)
		exec_cmd(((t_cmdnode *)head)->cmd, environ_cp, sesh);
	else if (head->type == LOGICAL_AND || head->type == LOGICAL_OR)
		exec_logicalop(((t_logicalop *)head), environ_cp, terminal, sesh);
	else if (head->type == AMPERSAND)
	{
		exec_tree((((t_ampersand *)head)->left), environ_cp, terminal, sesh);
		reset_fd(terminal);
		exec_tree((((t_ampersand *)head)->right), environ_cp, terminal, sesh);
		reset_fd(terminal);
	}
}
