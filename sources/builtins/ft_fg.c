/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:09:07 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/13 17:11:48 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	ft_fg(t_shell *sh, char **cmd)
{
	t_bg_jobs	*job;
	int			status;

	job = bg_fetch_node(sh, *(cmd + 1), "fg");
	if (job)
	{
		if (job->status == DONE || job->status == TERMINATED)
		{
			ft_err_print(NULL, "fg", "job has terminated", 2);
			return (0);
		}
		display_pipeline_cmd(sh, job);
		if (job->status == STOPPED || job->status == SUSPENDED)
			killpg(job->gpid, SIGCONT);
		if (ioctl(STDIN_FILENO, TIOCSPGRP, &job->gpid) == -1)
			exit_error(sh, 1, "ioctl error\n");
		transfer_to_fg(sh, job);
		job->status = RUNNING;
		waitpid(*job->pid, &status, WUNTRACED);
		catch_suspended_process(sh, status);
	}
	return (0);
}
