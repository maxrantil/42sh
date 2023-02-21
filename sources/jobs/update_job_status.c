/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_job_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:28:17 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/21 13:09:11 by mrantil          ###   ########.fr       */
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
	sh->exit_stat = WTERMSIG(status) + 128;
}

static void	job_exited(t_shell *sh, pid_t pid, int status)
{
	sh->exit_stat = WEXITSTATUS(status);
	if (sh->exit_stat == 126)
		change_process_status(sh->bg_node, pid, EXITED);
	else
		change_process_status(sh->bg_node, pid, DONE);
}

static void	job_suspended(t_shell *sh, pid_t pid, int status, int mode)
{
	t_bg_jobs	*node;

	change_process_status(sh->bg_node, pid, STOPPED);
	if (sh->fg_node->gpid)
		transfer_to_bg(sh, STOPPED);
	if (mode)
		display_suspended_job(sh, pid);
	node = sh->bg_node;
	while (node)
	{
		if (node->gpid == pid)
		{
			node->status = STOPPED;
			break ;
		}
		node = node->next;
	}
	if (node)
		queue_move_to_front(sh, node);
	sh->exit_stat = WSTOPSIG(status) + 128;
}

void	update_job_status(t_shell *sh, int status, int pid, int mode)
{
	int	ret;

	if (WIFSIGNALED(status))
	{
		ret = WTERMSIG(status);
		if (mode && ret == SIGINT)
			ft_putchar('\n');
		job_terminated(sh, pid, status);
		job_wtermsig_msg(ret);
	}
	else if (WIFEXITED(status))
		job_exited(sh, pid, status);
	else if (WIFSTOPPED(status))
		job_suspended(sh, pid, status, mode);
}
