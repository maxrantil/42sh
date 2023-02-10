/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:54 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/09 19:09:06 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	ft_jobs(t_shell *sh)
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
	return (0);
}
