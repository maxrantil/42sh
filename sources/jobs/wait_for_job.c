/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:07:13 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/25 17:18:04 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	kill_pipeline(t_shell *sh, int status)
{
	int	i;

	i = 0;
	if (!WIFSTOPPED(status))
	{
		while (sh->fg_node->pid[i])
		{
			kill(sh->fg_node->pid[i], SIGINT);
			waitpid(sh->fg_node->pid[i], &status, 0);
			i++;
		}
	}
}

void	wait_for_job(t_shell *sh, int pid)
{
	int	status;

	if (sh->ampersand)
		waitpid(pid, &status, WNOHANG | WUNTRACED);
	else if (sh->pipe->piping && sh->pipe->write_pipe[1] >= 0)
	{
		waitpid(pid, &status, WNOHANG);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		kill_pipeline(sh, status);
	}
	if (!sh->ampersand)
		update_job_status(sh, status, pid, 1);
}
