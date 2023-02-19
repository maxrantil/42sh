/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:09:07 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/19 14:42:12 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	ft_fg(t_shell *sh, char **cmd)
{
	t_bg_jobs	*job;

	job = bg_fetch_node(sh, *(cmd + 1), "fg");
	if (job)
	{
		if (job->status == DONE || job->status == TERMINATED)
		{
			ft_err_print(NULL, "fg", "job has terminated", 2);
			return (0);
		}
		display_pipeline_cmd(sh, job);
		if (ioctl(sh->pipe->stdincpy, TIOCSPGRP, &job->gpid) == -1)
			exit_error(sh, 1, "ioctl error\n");
		if (job->status == STOPPED || job->status == SUSPENDED)
			killpg(job->gpid, SIGCONT);
		transfer_to_fg(sh, job);
		job->status = RUNNING;
		wait_for_job(sh, job->gpid);
		ft_raw_disable(sh->orig_termios);
	}
	return (0);
}
