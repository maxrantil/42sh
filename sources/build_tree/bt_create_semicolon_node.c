/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create_semicolon_node.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:43:28 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/25 02:10:13 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_treenode	*init_semicolon(void)
{
	t_treenode	*semicolon;

	semicolon = ft_memalloc(sizeof(*semicolon));
	semicolon->type = SEMICOLON;
	(((t_semicolon *)semicolon)->type) = SEMICOLON;
	(((t_semicolon *)semicolon)->left) = NULL;
	(((t_semicolon *)semicolon)->right) = NULL;
	return (semicolon);
}

static int	next_semicolon_or_ampers(t_token *tokens, int i_tok, int end)
{
	int			next_semicol;
	int			next_ampersand;

	next_semicol = foreseer_of_tokens(tokens, SEMICOLON, i_tok, end);
	next_ampersand = foreseer_of_tokens(tokens, AMPERSAND, i_tok, end);
	if (next_semicol >= 0)
	{
		if (next_ampersand < 0)
			return (next_semicol);
		if (next_semicol < next_ampersand)
			return (next_semicol);
	}
	return (next_ampersand);
}

static int	init_values(int next_op,
		t_token *tokens, int i_tok, t_treenode **semi_or_amp)
{
	int	type;

	if (next_op >= 0)
		type = tokens[next_op].token;
	else
		type = tokens[i_tok].token;
	if (type == AMPERSAND)
		*semi_or_amp = init_ampersand_node();
	else
		*semi_or_amp = init_semicolon();
	return (type);
}

static void	split(t_token *tokens, t_treenode *semi_or_amp,
		int next_op, int type_delim[2])
{
	int	type;
	int	end;

	type = type_delim[0];
	end = type_delim[1];
	if (next_op >= 0)
	{
		if (type == AMPERSAND)
			(((t_ampersand *)semi_or_amp)->right) = create_semicolon_node(
					tokens, next_op + 1, end);
		else
			(((t_semicolon *)semi_or_amp)->right) = create_semicolon_node(
					tokens, next_op + 1, end);
	}
}

t_treenode	*create_semicolon_node(t_token *tokens, int i_tok, int end)
{
	t_treenode	*semi_or_amp;
	int			next_op;
	int			type_delim[2];

	(void)end;
	if (!tokens[i_tok].token)
		return (NULL);
	next_op = next_semicolon_or_ampers(tokens, i_tok, calculate_tokens(tokens));
	type_delim[0] = init_values(next_op, tokens, i_tok, &semi_or_amp);
	if (next_op >= 0)
		type_delim[1] = next_op;
	else
		type_delim[1] = calculate_tokens(tokens);
	if (type_delim[0] == AMPERSAND)
	{
		(((t_ampersand *)semi_or_amp)->left) = create_logical_op_tree(tokens,
				i_tok, type_delim[1]);
	}
	else
	{
		(((t_semicolon *)semi_or_amp)->left) = create_logical_op_tree(tokens,
				i_tok, type_delim[1]);
	}
	split(tokens, semi_or_amp, next_op, type_delim);
	return (semi_or_amp);
}
