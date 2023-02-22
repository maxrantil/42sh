/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_process_group.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:56:32 by mike_baru         #+#    #+#             */
/*   Updated: 2023/02/21 14:15:50 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	set_process_group(t_shell *sh, pid_t pid)
{
	if (!sh->fg_node->gpid)
	{
		setpgid(pid, 0);
		sh->fg_node->gpid = pid;
		if (!sh->ampersand)
		{
			// ft_printf("terminal: %s\n", sh->terminal);
			// int ret = open(sh->terminal, O_RDWR);
			// ft_printf("ret: %d\n", ret);
			if (ioctl(sh->pipe->stdincpy, TIOCSPGRP, &sh->fg_node->gpid) == -1)
				exit_error(sh, 1, "ioctl error in set_process_group()");
			// close (ret);
		}
	}
	else
		setpgid(pid, sh->fg_node->gpid);
}
