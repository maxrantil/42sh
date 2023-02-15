/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reap_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:22:04 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/14 15:02:44 by mbarutel         ###   ########.fr       */
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
		update_job_status(sh, status, pid);
		pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
	}
}
