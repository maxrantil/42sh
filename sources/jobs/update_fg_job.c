/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fg_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/08 00:03:48 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_42sh.h"

void	update_fg_job(t_shell *sh, pid_t pid, char **cmd)
{
	/* We reconnect stdin so that ioctl does not fail */
	if (sh->pipe->redir_in && dup2(sh->pipe->stdincpy, STDIN_FILENO) == -1)
		exit_error(sh, 1, "dup2 error in update_fg_job()");
    set_process_group(sh, pid);
	append_pid_arr(sh->fg_node, pid);
	append_cmd_arr(sh->fg_node, cmd);
}
