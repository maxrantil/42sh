/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_to_bg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:01:18 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/21 13:28:13 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	queue_add(t_shell *sh, int index)
{
	int			i;
	t_bg_jobs	*tmp;

	i = 0;
	tmp = sh->bg_node;
	while (tmp)
	{
		if (tmp->index == sh->process_queue[i])
		{
			if (tmp->status == STOPPED)
			{
				i++;
				tmp = sh->bg_node;
			}
		}
		tmp = tmp->next;
	}
	++sh->process_count;
	ft_memmove(&sh->process_queue[i + 1], \
	&sh->process_queue[i], sh->process_count * sizeof(int));
	sh->process_queue[i] = index;
}

static t_bg_jobs	*init_bg_node(t_shell *sh, int status, \
int index, t_bg_jobs *prev)
{
	t_bg_jobs	*bg_node;

	bg_node = (t_bg_jobs *)ft_memalloc(sizeof(t_bg_jobs));
	bg_node->gpid = sh->fg_node->gpid;
	init_pid(sh, bg_node);
	init_cmd(sh, bg_node);
	bg_node->status = status;
	bg_node->index = index;
	queue_add(sh, index);
	bg_node->prev = prev;
	bg_node->next = NULL;
	return (bg_node);
}

static bool	fg_to_bg(t_shell *sh, t_bg_jobs	**job, int status)
{
	t_bg_jobs	*prev;

	prev = NULL;
	*job = sh->bg_node;
	while (*job)
	{
		if (sh->fg_node->gpid == (*job)->gpid)
		{
			(*job)->status = status;
			queue_move_to_front(sh, *job);
			return (false);
		}
		prev = *job;
		*job = (*job)->next;
	}
	*job = prev;
	return (true);
}

void	transfer_to_bg(t_shell *sh, int status)
{
	t_bg_jobs	*job;

	if (sh->process_count < JOBS_MAX)
	{
		if (!sh->bg_node)
		{
			sh->bg_node = init_bg_node(sh, status, 0, NULL);
			return ;
		}
		else if (fg_to_bg(sh, &job, status))
			job->next = init_bg_node(sh, status, job->index + 1, job);
	}
	else
		ft_putendl_fd("42sh: too many jobs\n", 2);
}
