/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reap_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:22:04 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/13 21:23:54 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void reap_process(t_shell *sh)
{
    int pid;
    int status;
    
	pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
	while (pid > 0)
	{
		update_job_status(sh, status, pid);
		pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
	}
}
