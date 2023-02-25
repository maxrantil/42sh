/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fg_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:35 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/25 17:11:08 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It sets the process group of the given pid that is first in the pipeline.
 * It then appends the pid and command to the foreground node.
 *
 * @param sh the shell struct
 * @param pid the pid of the process that was just created
 * @param cmd The command to be executed.
 */
void	update_fg_job(t_shell *sh, pid_t pid, char **cmd)
{
	set_process_group(sh, pid);
	append_pid_arr(sh->fg_node, pid);
	append_cmd_arr(sh->fg_node, cmd);
}
