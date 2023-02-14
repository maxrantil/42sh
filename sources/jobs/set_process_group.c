/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_process_group.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:56:32 by mike_baru         #+#    #+#             */
/*   Updated: 2023/02/14 12:54:07 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	set_process_group(t_shell *sh, pid_t pid)
{
	if (!sh->fg_node->gpid)
	{
		setpgid(pid, 0);
		// ft_printf("setpgid %d\n", pid);
		sh->fg_node->gpid = pid;
		if (!sh->ampersand)
		{
			// if (ioctl(sh->pipe->stdincpy, TIOCSPGRP, &sh->fg_node->gpid) == -1)
			// 	exit_error(sh, 1, "ioctl error in set_process_group()");

			// ft_printf("before error %d\n", sh->fg_node->gpid);
			if (ioctl(sh->pipe->stdincpy, TIOCSPGRP, &sh->fg_node->gpid) == -1)
				exit_error(sh, 1, "ioctl error in set_process_group()");
			// ft_printf("after error\n");
		}
	}
	else
		setpgid(pid, sh->fg_node->gpid);
}
