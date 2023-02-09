/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fg_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/09 15:49:30 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_42sh.h"

void	update_fg_job(t_shell *sh, pid_t pid, char **cmd)
{
	// int	temp_pipe[2];
//
	// temp_pipe[0] = -1;
	// temp_pipe[1] = -1;
	// ft_putstr_fd(*cmd, 2);
	// ft_putstr_fd(" HELLO\n", 2);
	// ft_putnbr_fd(sh->pipe->write_pipe[0], 2);
	// ft_putstr_fd("\n", 2);
	// if (sh->pipe->write_pipe[0] >= 0)
		// temp_pipe[0] = dup(sh->pipe->write_pipe[0]);
	// temp_pipe[1] = dup(sh->pipe->write_pipe[1]);

	/* We reconnect stdin so that ioctl does not fail */
	if (sh->pipe->redir_in || sh->pipe->write_pipe[0] >= 0)
	{
		// if (sh->pipe->write_pipe[0] >= 0)
		// {
			// close(sh->pipe->write_pipe[0]);
			// sh->pipe->write_pipe[0] = -1;
		// }
		// if (dup2(sh->pipe->stdincpy, STDIN_FILENO) == -1)
			// exit_error(sh, 1, "dup2 error in update_fg_job()");
	}
    set_process_group(sh, pid);
	append_pid_arr(sh->fg_node, pid);
	append_cmd_arr(sh->fg_node, cmd);
	// close(sh->pipe->write_pipe[1]);
	// sh->pipe->write_pipe[1] = -1;
	// if (temp_pipe[0] >= 0)
		// sh->pipe->write_pipe[0] = dup(temp_pipe[0]);
	// sh->pipe->write_pipe[1] = dup(temp_pipe[1]);
}
