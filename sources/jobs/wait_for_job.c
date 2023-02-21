/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:07:13 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/21 15:40:42 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	wait_for_job(t_shell *sh, int pid)
{
	int	status;

	// ft_printf("pid %d\n", pid);
	// ft_printf("write pipe [0] -> %2d : [1] -> %2d\n", sh->pipe->write_pipe[0], sh->pipe->write_pipe[1]);
	// ft_printf("read  pipe [0] -> %2d : [1] -> %2d\n", sh->pipe->read_pipe[0], sh->pipe->read_pipe[1]);
	if (sh->ampersand)
		waitpid(pid, &status, WNOHANG | WUNTRACED);
	else if (sh->pipe->piping && sh->pipe->write_pipe[1] >= 0
		/*&& sh->pipe->read_pipe[0] >= 0*/)
	{
		// close(sh->pipe->write_pipe[1]);
		// close(sh->pipe->read_pipe[0]);
		ft_putendl("wait for job BEFORE\n");
		waitpid(pid, &status, WNOHANG);
		ft_putendl("wait for job\n");
	}
	else
		waitpid(pid, &status, WUNTRACED);
	if (!sh->ampersand)
		update_job_status(sh, status, pid, 1);
}
