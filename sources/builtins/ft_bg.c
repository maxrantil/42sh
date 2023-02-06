/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:03:43 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/06 19:19:47 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	add_to_index_pos_of_queue(t_shell *sh, t_bg_jobs *job)
{
	ft_memmove(&sh->process_queue[sh->process_count - job->index + 1], \
	&sh->process_queue[sh->process_count - job->index], sh->process_count * sizeof(int));
	sh->process_queue[sh->process_count - job->index] = job->index;
}

int ft_bg(t_shell *sh, char **cmd)
{
	t_bg_jobs   *job;

	job = bg_fetch_node(sh, *(cmd + 1));
	if (!job)
		ft_putstr("fg: no such job\n");
	else
	{
		ft_print_dbl_array(*job->cmd);
		ft_putchar('\n');
		if (job->status == STOPPED || job->status == SUSPENDED)
		{
			job->status = RUNNING;
			queue_delete(sh, job);
			add_to_index_pos_of_queue(sh, job);
			killpg(job->gpid, SIGCONT);
		}
		else
			ft_err_print(NULL, "bg", "job already in the background", 2);
	}
	return (0);
}