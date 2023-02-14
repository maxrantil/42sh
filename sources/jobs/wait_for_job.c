/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:07:13 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/14 13:00:44 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	wait_for_job(t_shell *sh, int pid)
{
	int	status;

	if (sh->ampersand)
		waitpid(pid, &status, WNOHANG | WUNTRACED);
	else if (!sh->pipe->piping)
		waitpid(pid, &status, WUNTRACED);
	if (!sh->ampersand)
		update_job_status(sh, status, pid);
}
