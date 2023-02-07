/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:07:27 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/07 11:09:01 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static bool	check_bg_pipeline(t_bg_jobs *job, pid_t pid)
{
	pid_t	*ptr;

	ptr = job->pid;
	while (*ptr)
	{
		if (*ptr == pid)
			return (true);
		ptr++;
	}
	return (false);
}

static void    change_process_status(t_bg_jobs *bg_node, int pid, int status)
{
    t_bg_jobs    *job;

    job = bg_node;
    while (job)
	{
		if (check_bg_pipeline(job, pid))
			break ;	
        job = job->next;
	}
	if (job)
		job->status = status;
}

void	update_jobs(t_shell *sh, int pid, int status)
{
	if (WIFSIGNALED(status)) // This is for when a process has been signalled
	{
		ft_putchar('\n');
		if (WTERMSIG(status)) // This is for when the signal is termination
			change_process_status(sh->bg_node, pid, TERMINATED);
	}
	else if (WIFSTOPPED(status)) // This is for when the process has been suspended and can still continue
	{
		ft_printf("Suspended\n");
		transfer_to_bg(sh, STOPPED);
		display_suspended_job(sh);
		reset_fgnode(sh);
	}
	else if (WIFEXITED(status)) // This is for when the process has exited without interruption
		change_process_status(sh->bg_node, pid, DONE);
}
