/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_init_logical_op.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:36:18 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/17 09:36:49 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_treenode	*init_logical_op(int type)
{
	t_treenode	*logical_op;

	logical_op = ft_memalloc(sizeof(*logical_op));
	logical_op->type = type;
	((t_logicalop *)logical_op)->type = type;
	((t_logicalop *)logical_op)->left = NULL;
	((t_logicalop *)logical_op)->right = NULL;
	return (logical_op);
}
