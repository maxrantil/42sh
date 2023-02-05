/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_job_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:32:14 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/05 12:40:08 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	display_state(int status)
{
	if (status == DONE)
		ft_printf("%2s%-24s", "", "Done");
	else if (status == STOPPED)
		ft_printf("%2s%-24s", "", "Stopped");
	else if (status == TERMINATED)
		ft_printf("%2s%-24s", "", "Terminated");
	else if (status == SUSPENDED)
		ft_printf("%2s%-24s", "", "Suspended");
	else
		ft_printf("%2s%-24s", "", "Running");
}

static void	print_queue(t_shell *sh, int index)
{
	if (sh->process_queue[0] == index)
		ft_putchar('+');
	else if (sh->process_queue[1] == index)
		ft_putchar('-');
	else
		ft_putchar(' ');
}

void	display_job_node(t_shell *sh, t_bg_jobs *job)
{
	if (job)
	{
		ft_printf("[%d]", job->index + 1);
		print_queue(sh, job->index);
		display_state(job->status);
		display_pipeline_cmd(job);
		if (job->status == DONE || job->status == TERMINATED)
			bg_node_delete(sh, &job);
	}
}
