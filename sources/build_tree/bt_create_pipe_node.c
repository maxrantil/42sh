/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create_pipe_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:00:54 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/28 21:22:47 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static t_treenode	*init_pipe(t_treenode *left, t_treenode *right)
{
	t_treenode	*node;

	node = ft_memalloc(sizeof(*node));
	node->type = PIPE;
	((t_pipenode *)node)->type = PIPE;
	((t_pipenode *)node)->left = left;
	((t_pipenode *)node)->right = right;
	return (node);
}

t_treenode	*create_pipe_node(t_token *tokens, int i_tok, int end)
{
	t_treenode	*left;
	t_treenode	*right;
	int			next_pipe;

	left = NULL;
	right = NULL;
	if (tokens[i_tok].token == PIPE)
	{
		left = parse_left_cmd(tokens, i_tok - 1);
		next_pipe = foreseer_of_tokens(tokens, PIPE, i_tok + 1,
				end);
		if (next_pipe >= 0)
			right = create_pipe_node(tokens, next_pipe, end);
		else
			right = parse_right_cmd(tokens, i_tok + 1);
		return (init_pipe(left, right));
	}
	return (NULL);
}
