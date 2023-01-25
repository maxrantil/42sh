/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_check_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:40:19 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/13 13:50:15 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	check_type_split(t_treenode *root)
{
	if (root->type == SEMICOLON)
		ft_printf("[;]");
	else if (root->type == AMPERSAND)
		ft_printf("[&]");
}

void	check_type(t_treenode *root)
{
	if (!root)
		return ;
	else if (root->type == CMD && root->type)
		print_exec(root);
	else if (root->type == PIPE)
		ft_printf("[|]");
	else if (root->type == REDIR && ((t_redir *)root)->cmd->type == CMD
		&& ((t_redir *)root)->close_fd == STDOUT_FILENO
		&& ((t_redir *)root)->rights & O_APPEND)
		ft_printf(">> [%d] [%s]\n",
			root->type, *(((t_cmdnode *)((t_redir *)root)->cmd)->cmd));
	else if (root->type == REDIR
		&& ((t_redir *)root)->close_fd == STDOUT_FILENO)
		ft_printf("> [%d]\n", root->type);
	else if (root->type == REDIR && ((t_redir *)root)->close_fd == STDIN_FILENO)
		ft_printf("> [%d]\n", root->type);
	else if (root->type == AGGREGATION)
		ft_printf(">& [%d] [%s]\n", root->type, ((t_aggregate *)root)->cmd);
	else if (root->type == LOGICAL_AND)
		ft_printf("[&&]");
	else if (root->type == LOGICAL_OR)
		ft_printf("[||]");
	check_type_split(root);
}
