/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_node_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:10:49 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/01 18:41:45 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	delete_from_queue(t_shell *sh, t_bg_jobs *process)
{
	int	i;

	i = 0;
	while (i < sh->process_count)
	{
		if (process->index == sh->process_queue[i])
		{
			ft_memmove(&sh->process_queue[i], &sh->process_queue[i + 1], \
			(sh->process_count - 1 - i) * sizeof(int));
			sh->process_count--;
			break ;
		}
		i++;
	}
}

static void	remove_node(t_bg_jobs **curr)
{
	int		i;

	i = -1;
	reset_cmd(&(*curr)->cmd);
	ft_memdel((void **)&(*curr)->pid);
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