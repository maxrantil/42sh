/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_print_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:22:15 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/13 19:53:39 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	split_print_tree_again(t_treenode *root, int lvl)
{
	if (root->type == AGGREGATION)
		rec_print_tree(((t_aggregate *)root)->cmd, lvl);
	else if (root->type == AMPERSAND)
	{
		rec_print_tree(((t_ampersand *)root)->left, lvl);
		print_spaces(lvl);
		check_type(root);
		ft_printf("\n");
		rec_print_tree(((t_ampersand *)root)->right, lvl);
	}
	else if (root->type == CMD)
	{
		print_spaces(lvl);
		check_type(root);
	}
}

void	split_print_tree(t_treenode *root, int lvl)
{
	if (root->type == LOGICAL_AND || root->type == LOGICAL_OR)
	{
		rec_print_tree(((t_logicalop *)root)->left, lvl);
		print_spaces(lvl);
		check_type(root);
		ft_printf("\n");
		rec_print_tree(((t_logicalop *)root)->right, lvl);
	}
	else if (root->type == SEMICOLON)
	{
		rec_print_tree(((t_semicolon *)root)->left, lvl);
		print_spaces(lvl);
		check_type(root);
		ft_printf("\n");
		rec_print_tree(((t_semicolon *)root)->right, lvl);
	}
	split_print_tree_again(root, lvl);
}

void	rec_print_tree(t_treenode *root, int lvl)
{
	if (root == NULL)
		return ;
	lvl += COUNT;
	if (root->type == PIPE)
	{
		rec_print_tree(((t_pipenode *)root)->left, lvl);
		print_spaces(lvl);
		check_type(root);
		ft_printf("\n");
		rec_print_tree(((t_pipenode *)root)->right, lvl);
	}
	else if (root->type == REDIR)
	{
		print_spaces(lvl);
		check_type(root);
		rec_print_tree(((t_redir *)root)->cmd, lvl);
	}
	split_print_tree(root, lvl);
}

void	print_tree(t_treenode *head)
{
	write(1, "\n------------------ TREE PRINT ------------------\n", 51);
	if (head)
		rec_print_tree(head, 0);
	write(1, "\n------------------ TREE PRINT ------------------\n\n", 52);
}
