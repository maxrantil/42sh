/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reap_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:22:04 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/16 11:48:45 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It waits for a child process to change state, and then updates the job status
 *
 * @param sh the shell struct
 */
void	reap_process(t_shell *sh)
{
	int	pid;
	int	status;

	pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
	while (pid > 0)
	{
		update_job_status(sh, status, pid, 0);
		pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
	}
}
