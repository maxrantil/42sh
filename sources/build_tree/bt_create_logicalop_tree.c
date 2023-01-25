/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create_logicalop_tree.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:44:23 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/13 19:13:34 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_treenode	*init_logical_op(int type)
{
	t_treenode	*logical_op;

	logical_op = ft_memalloc(sizeof(*logical_op));
	logical_op->type = type;
	((t_logicalop *)logical_op)->type = type;
	((t_logicalop *)logical_op)->left = NULL;
	((t_logicalop *)logical_op)->right = NULL;
	return (logical_op);
}

static int	next_logical_op(t_token *tokens, int i_tok, int semicol)
{
	int	logical_and;
	int	logical_or;

	logical_and = foreseer_of_tokens(tokens, LOGICAL_AND, i_tok, semicol);
	logical_or = foreseer_of_tokens(tokens, LOGICAL_OR, i_tok, semicol);
	if (logical_and >= 0)
	{
		if (logical_or < 0)
			return (logical_and);
		else if (logical_and < logical_or)
			return (logical_and);
	}
	if (logical_or >= 0)
	{
		if (logical_and < 0)
			return (logical_or);
		else if (logical_or < logical_and)
			return (logical_or);
	}
	return (-1);
}

static int	logical_op_type(t_token *tokens, int logical_op)
{
	if (tokens[logical_op].token == LOGICAL_AND)
		return (LOGICAL_AND);
	return (LOGICAL_OR);
}

static t_treenode	*create_logical_op_node(t_token *tokens,
					int idx_logical_op, int semicol)
{
	t_treenode	*logical_op;
	int			next_op_node;
	int			start_of_left_cmd;

	logical_op = init_logical_op(logical_op_type(tokens, idx_logical_op));
	next_op_node = next_logical_op(tokens, idx_logical_op + 1, semicol);
	if (next_op_node >= 0)
		((t_logicalop *)logical_op)->right
			= create_logical_op_node(tokens, next_op_node, semicol);
	start_of_left_cmd = idx_logical_op - 1;
	while (start_of_left_cmd > 0
		&& !is_semicolon_or_ampersand(tokens[start_of_left_cmd].token)
		&& !is_logicalop(tokens[start_of_left_cmd].token))
		--start_of_left_cmd;
	if (start_of_left_cmd > 0)
		++start_of_left_cmd;
	((t_logicalop *)logical_op)->left
		= create_command_tree(tokens, start_of_left_cmd, idx_logical_op);
	if (((t_logicalop *)logical_op)->right == NULL)
		((t_logicalop *)logical_op)->right
			= create_command_tree(tokens, idx_logical_op + 1, semicol);
	return (logical_op);
}

t_treenode	*create_logical_op_tree(t_token *tokens, int i_tok, int semicol)
{
	int			logical_op;
	t_treenode	*head;

	logical_op = next_logical_op(tokens, i_tok, semicol);
	if (logical_op >= 0)
		head = create_logical_op_node(tokens, logical_op, semicol);
	else
		head = create_command_tree(tokens, i_tok, semicol);
	return (head);
}
