/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_job_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:28:17 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/16 15:49:53 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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

static void	job_terminated(t_shell *sh, pid_t pid, int status)
{
	check_fg_pipeline(sh, pid);
	change_process_status(sh->bg_node, pid, TERMINATED);
	sh->exit_stat = WTERMSIG(status) + 127;
}

static void	job_exited(t_shell *sh, pid_t pid, int status)
{
	sh->exit_stat = WEXITSTATUS(status);
	if (sh->exit_stat == 126)
		change_process_status(sh->bg_node, pid, EXITED);
	else
		change_process_status(sh->bg_node, pid, DONE);
}

static void	job_suspended(t_shell *sh, pid_t pid, int status)
{
	change_process_status(sh->bg_node, pid, STOPPED);
	if (sh->fg_node->gpid)
		transfer_to_bg(sh, STOPPED);
	display_suspended_job(sh, pid);
	sh->exit_stat = WSTOPSIG(status) + 127;
}

void	update_job_status(t_shell *sh, int status, int pid, int mode)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status))
		{
			if (mode)
				ft_putchar('\n');
			job_terminated(sh, pid, status);
		}
	}
	else if (WIFEXITED(status))
		job_exited(sh, pid, status);
	else if (WIFSTOPPED(status))
		job_suspended(sh, pid, status);
}
