/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_node_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:10:49 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/10 17:15:12 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	remove_node(t_bg_jobs **curr)
{
	reset_cmd(&(*curr)->cmd);
	ft_memdel((void **)&(*curr)->pid);
	ft_memdel((void **)&(*curr));
}

void	bg_node_delete(t_shell *sh, t_bg_jobs **curr)
{
	t_bg_jobs	*next;
	t_bg_jobs	*prev;

	prev = (*curr)->prev;
	next = (*curr)->next;
	delete_from_queue(sh, *curr);
	remove_node(curr);
	if (prev)
		prev->next = next;
	else
		sh->bg_node = next;
	if (next)
		next->prev = prev;
	(*curr) = next;
}
