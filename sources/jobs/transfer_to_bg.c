/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_to_bg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:01:18 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/08 17:30:13 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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
	add_to_queue(sh, index);
	bg_node->prev = prev;
	bg_node->next = NULL;
	return (bg_node);
}

static void	signalled_from_background(t_bg_jobs *job, int status)
{
	while (job->next)
		job = job->next;
	job->status = status;
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
			delete_from_queue(sh, *job);
			ft_memmove(&sh->process_queue[1], \
			&sh->process_queue[0], (sh->process_count - 1) * sizeof(int));
			sh->process_queue[0] = (*job)->index;
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

	if (++sh->process_count < JOBS_MAX)
	{
		if (!sh->bg_node)
		{
			sh->bg_node = init_bg_node(sh, status, 0, NULL);
			return ;
		}
		if (sh->fg_node->gpid == 0)
		{
			signalled_from_background(sh->bg_node, status);
			return ;
		}
		else
		{
			if (fg_to_bg(sh, &job, status))
				job->next = init_bg_node(sh, status, job->index + 1, job);
		}
	}
	else
		ft_putendl_fd("42sh: too many jobs\n", 2);
}
