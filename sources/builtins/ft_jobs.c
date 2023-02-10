/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:54 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/10 16:28:47 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	display_no_flags(t_shell *sh)
{
	t_bg_jobs *job;

	job = sh->bg_node;
	while (job)
	{
        display_job_node(sh, job);
		if (job->status == DONE || job->status == TERMINATED)
			bg_node_delete(sh, &job);
		else
			job = job->next;
	}
}

// static void	display_l_flags(t_shell *sh)
// {
// 	t_bg_jobs	*job;

// 	job = sh->bg_node;
// 	while (job)
// 	{
// 		display_job_pipeline(sh, job);
// 		if (job->status == DONE || job->status == TERMINATED)
// 			bg_node_delete(sh, &job);
// 		else
// 			job = job->next;
// 	}
// }

// static void	display_p_flags(t_shell *sh)
// {
// 	t_bg_jobs	*job;

// 	job = sh->bg_node;
// 	while (job)
// 	{
// 		ft_printf("%d\n", *job->pid);
// 		if (job->status == DONE || job->status == TERMINATED)
// 			bg_node_delete(sh, &job);
// 		else
// 			job = job->next;
// 	}
// }

int	ft_jobs(t_shell *sh)
{
	display_no_flags(sh);
	// display_l_flags(sh);
	// display_p_flags(sh);
	return (0);
}
