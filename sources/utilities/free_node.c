/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:07:04 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/16 16:43:43 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	free_rest_two(t_treenode *head)
{
	if (head->type == LOGICAL_AND || head->type == LOGICAL_OR)
	{
		free_node(((t_logicalop *)head)->left);
		((t_logicalop *)head)->left = NULL;
		free_node(((t_logicalop *)head)->right);
		((t_logicalop *)head)->right = NULL;
	}
	else if (head->type == AMPERSAND)
	{
		free_node(((t_ampersand *)head)->left);
		((t_ampersand *)head)->left = NULL;
		free_node(((t_ampersand *)head)->right);
		((t_ampersand *)head)->right = NULL;
	}
	ft_memdel((void **)&head);
}

static void	free_rest_one(t_treenode *head)
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
	free_rest_two(head);
}

void	free_node(t_treenode *head)
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
	free_rest_one(head);
}
