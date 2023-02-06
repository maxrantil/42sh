/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_to_bg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:01:18 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/06 11:10:51 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void    delete_from_queue(t_shell *sh, t_bg_jobs *process)
{
    int    i;

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

static void	init_pid(t_shell *sh, t_bg_jobs *bg_node)
{
	int	len;

	len = 0;
	while (sh->fg_node->pid[len])
		len++;
	bg_node->pid = (pid_t *)ft_memalloc(sizeof(pid_t) * (len + 1));
	bg_node->pid[len] = 0;
	while (--len >= 0)
		bg_node->pid[len] = sh->fg_node->pid[len];
}

static void	init_cmd(t_shell *sh, t_bg_jobs *bg_node)
{
	int	len;

	len = triple_ptr_len(sh->fg_node->cmd);
	bg_node->cmd = (char ***)ft_memalloc(sizeof(char **) * (len + 1));
	bg_node->cmd[len] = NULL;
	while (--len >= 0)
		bg_node->cmd[len] = dup_dbl_ptr(sh->fg_node->cmd[len]);
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
	ft_memmove(&sh->process_queue[1], \
	&sh->process_queue[0], (sh->process_count - 1) * sizeof(int));
	sh->process_queue[0] = index;
	bg_node->prev = prev;
	bg_node->next = NULL;
	return (bg_node);
}

void	transfer_to_bg(t_shell *sh, int status)
{
	t_bg_jobs	*job;
	t_bg_jobs	*prev;

	if (++sh->process_count < JOBS_MAX)
	{
		prev = NULL;
		if (!sh->bg_node)
		{
			sh->bg_node = init_bg_node(sh, status, 0, prev);
			return ;
		}
		if (sh->fg_node->gpid == 0)
		{
			job = sh->bg_node;
			while (job->next)
				job = job->next;
			job->status = STOPPED;
			return ;
		}	
		else
		{
			job = sh->bg_node;
			while (job)
			{
				if (sh->fg_node->gpid == job->gpid)
				{
					job->status = STOPPED;
					delete_from_queue(sh, job);
					ft_memmove(&sh->process_queue[1], \
					&sh->process_queue[0], (sh->process_count - 1) * sizeof(int));
					sh->process_queue[0] = job->index;
					reset_fgnode(sh);
					return ;
				}
				prev = job;
				job = job->next;
			}
			prev->next = init_bg_node(sh, status, prev->index + 1, prev);
		}
	}
	else
	{
		ft_putendl_fd("42sh: too many jobs\n", 2);
		return ;
	}
}
