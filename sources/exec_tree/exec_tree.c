/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:23:35 by jakken            #+#    #+#             */
/*   Updated: 2023/01/27 11:39:52 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_42sh.h"

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

static void remove_shared_memory(t_shell *sh)
{
	if (shmctl(sh->shared_mem_id, IPC_RMID, NULL) < 0 || shmctl(sh->shared_mem_index, IPC_RMID, NULL) < 0)
	{
		ft_err_print(NULL, "shmctk", "failed to delete shared memory", 2);
		exit (1);
	}
}

void	exec_tree(t_treenode *head, char ***environ_cp,
				char *terminal, t_shell *sh)
{
	if (!head)
		return ;
	if (head->type == SEMICOLON)
	{
		//Fg things
	sh->shared_mem_id = shmget(IPC_PRIVATE, sizeof(int) * 255, IPC_CREAT | 0666); //Move to appropriate place at merge
	sh->shared_mem_index = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666); //Move to appropriate place at merge
		if (sh->shared_mem_id < 0 || sh->shared_mem_index < 0) //Move these also
	{
		ft_err_print(NULL, "shmget", "no memory available", 2);
		exit (1);
	}
		exec_tree((((t_semicolon *)head)->left), environ_cp, terminal, sh);
		remove_shared_memory(sh);
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
		exec_cmd(((t_cmdnode *)head)->cmd, environ_cp, sh);
	else if (head->type == LOGICAL_AND || head->type == LOGICAL_OR)
		exec_logicalop(((t_logicalop *)head), environ_cp, terminal, sh);
	else if (head->type == AMPERSAND)
	{
		exec_tree((((t_ampersand *)head)->left), environ_cp, terminal, sh);
		reset_fd(terminal);
		exec_tree((((t_ampersand *)head)->right), environ_cp, terminal, sh);
		reset_fd(terminal);
	}
}
