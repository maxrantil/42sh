/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create_semicolon_node.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:43:28 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/25 16:02:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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

int	next_semicolon_or_ampersand(t_token *tokens, int i_tok, int end)
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

static int init_values(int next_semi_or_amp,
		t_token *tokens, int i_tok, t_treenode **semi_or_amp)
{
	int	type;

	if (next_semi_or_amp >= 0)
		type = tokens[next_semi_or_amp].token;
	else
		type = tokens[i_tok].token;
	if (type == AMPERSAND)
		*semi_or_amp = init_ampersand_node();
	else
		*semi_or_amp = init_semicolon();
	return (type);
}

/*	<cmd>& buts it in the background,
	doing <samecmd>& again kills the old and stars a new */
/* man kill -> SIGCONT, could be answer for vim ctrl+z problem */
t_treenode	*create_semicolon_node(t_token *tokens, int i_tok, int end)
{
	t_treenode	*semi_or_amp;
	int			next_semi_or_amp;
	int			type;
	int			delim;

	if (!tokens[i_tok].token)
		return (NULL);
	next_semi_or_amp = next_semicolon_or_ampersand(tokens, i_tok, end);
	type = init_values(next_semi_or_amp, tokens, i_tok, &semi_or_amp);
	if (next_semi_or_amp >= 0)
		delim = next_semi_or_amp;
	else
		delim = end;
	if (type == AMPERSAND)
	{
		(((t_ampersand *)semi_or_amp)->left) = create_logical_op_tree(tokens,
				i_tok, delim);
	}
	else
	{
		(((t_semicolon *)semi_or_amp)->left) = create_logical_op_tree(tokens,
				i_tok, delim);
	}
	//next_semi_or_amp = next_semicolon_or_ampersand(tokens, next_semi_or_amp + 1, end);
	if (next_semi_or_amp >= 0)
	{
		if (type == AMPERSAND)
			(((t_ampersand *)semi_or_amp)->right) = create_semicolon_node(
					tokens, next_semi_or_amp + 1, end);
		else
			(((t_semicolon *)semi_or_amp)->right) = create_semicolon_node(
					tokens, next_semi_or_amp + 1, end);
	}
	return (semi_or_amp);
}
