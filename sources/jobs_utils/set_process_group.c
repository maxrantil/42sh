# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
/*   set_process_group.c                                :+:      :+:    :+:   */
#                                                     +:+ +:+         +:+      #
#    By: mike_barutel <marvin@42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 11:56:32 by mike_baru         #+#    #+#              #
/*   Updated: 2023/01/31 12:08:10 by mike_baru        ###   ########.fr       */
#                                                                              #
# **************************************************************************** #

#include "ft_42sh.h"

void	set_process_group(t_shell *sh, pid_t pid)
{
	if (!sh->fg_node.pgid)
	{
		setpgid(pid, 0); // This sets up the pid as its own pgid
		sh->fg_node.gpid = pid;
	}
	else
		setpgid(pid, sh->fg_node.pgid);
	// Append pid to array of pids
	// Append command to array of **cmd
}

