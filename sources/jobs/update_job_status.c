/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_job_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:28:17 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/16 11:48:01 by mrantil          ###   ########.fr       */
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

static void	change_process_status(t_bg_jobs *bg_node, pid_t pid, int status)
{
	t_bg_jobs	*job;

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

static void	check_fg_pipeline(t_shell *sh, pid_t pid)
{
	pid_t	*ptr;

	if (!sh->fg_node->gpid)
		return ;
	ptr = sh->fg_node->pid;
	while (ptr && *ptr)
	{
		if (*ptr == pid)
		{
			reset_fgnode(sh);
			return ;
		}
		ptr++;
	}
}

void	update_job_status(t_shell *sh, int status, int pid, int mode)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status))
		{
			if (mode)
				ft_putchar('\n');
			check_fg_pipeline(sh, pid);
			change_process_status(sh->bg_node, pid, TERMINATED);
			sh->exit_stat = WTERMSIG(status) + 127;
		}
	}
	else if (WIFEXITED(status))
	{
		sh->exit_stat = WEXITSTATUS(status);
		if (sh->exit_stat == 126)
			change_process_status(sh->bg_node, pid, EXITED);
		else
			change_process_status(sh->bg_node, pid, DONE);
	}
	else if (WIFSTOPPED(status))
	{
		change_process_status(sh->bg_node, pid, STOPPED);
		if (sh->fg_node->gpid)
			transfer_to_bg(sh, STOPPED);
		display_suspended_job(sh, pid);
		sh->exit_stat = WSTOPSIG(status) + 127;
	}
}
