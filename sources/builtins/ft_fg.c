/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:09:07 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/11 18:20:39 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	ft_fg(t_shell *sh, char **cmd)
{
    t_bg_jobs   *job;
	int		    status;

	job = bg_fetch_node(sh, cmd);
	if (job)
	{
		if (job->status == DONE || job->status == TERMINATED)
		{
			display_job_node(sh, job);
			return (0);
		}
		display_pipeline_cmd(job);
		if (job->status == STOPPED || job->status == SUSPENDED)
			killpg(job->gpid, SIGCONT);
		if (ioctl(STDIN_FILENO, TIOCSPGRP, &job->gpid) == -1)
				exit(1); // this needs to be proper exit
		transfer_to_fg(sh, job);
		job->status = RUNNING;
		waitpid(*job->pid, &status, WUNTRACED);
	}
	return (0);
}
