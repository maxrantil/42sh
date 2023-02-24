/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:07:13 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/24 22:47:44 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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
		if (!WIFSTOPPED(status))
		{
			ft_printf("KILLKILLKILL STATUS: %d\n", status);
			kill(sh->fg_node->gpid, SIGINT);
		}
	}
	if (!sh->ampersand)
		update_job_status(sh, status, pid, 1);
}
