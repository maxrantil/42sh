/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:07:13 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/14 08:40:59 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	wait_for_job(t_shell *sh, int pid)
{
	int	wait_flag;
	int	status;

	wait_flag = WUNTRACED;
	if (sh->ampersand)
		wait_flag |= WNOHANG;
	waitpid(pid, &status, wait_flag);
	if (!sh->ampersand)
		update_job_status(sh, status, pid);
}
