/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_create_ampersand_node.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:56:47 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/26 09:55:22 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_treenode	*init_ampersand_node(void)
{
	t_treenode	*ampersand;

	ampersand = ft_memalloc(sizeof(t_treenode));
	ampersand->type = AMPERSAND;
	((t_ampersand *)ampersand)->type = AMPERSAND;
	((t_ampersand *)ampersand)->left = NULL;
	((t_ampersand *)ampersand)->right = NULL;
	return (ampersand);
}

/*
t_treenode *create_ampersand_node(t_token *tokens, int i_tok, int end)
{
	t_treenode *ampersand;

	ampersand = init_ampersand_node();

}
*/
