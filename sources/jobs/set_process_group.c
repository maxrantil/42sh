/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_process_group.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:56:32 by mike_baru         #+#    #+#             */
/*   Updated: 2023/02/06 14:42:10 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	set_process_group(t_shell *sh, pid_t pid)
{
	if (!sh->fg_node->gpid)
	{
		setpgid(pid, 0); // This sets up the pid as its own pgid
		sh->fg_node->gpid = pid;
		if (!sh->ampersand)
		{
			if (ioctl(STDIN_FILENO, TIOCSPGRP, &sh->fg_node->gpid) == -1)
				ft_exit(sh, 1); // this needs to be proper exit
		}
	}
	else
		setpgid(pid, sh->fg_node->gpid);
}





// void	set_process_group(t_shell *sh, pid_t pid)
// {
// 	if (!sh->fg_node->gpid)
// 	{
// 		setpgid(pid, 0); // This sets up the pid as its own pgid
// 		sh->fg_node->gpid = pid;
// 		if (!sh->ampersand)
// 		{
// 			if (ioctl(STDIN_FILENO, TIOCSPGRP, &sh->fg_node->gpid) == -1)
// 				ft_exit(sh, 1); // this needs to be proper exit
// 		}
// 	}
// 	else
// 		setpgid(pid, sh->fg_node->gpid);
// }