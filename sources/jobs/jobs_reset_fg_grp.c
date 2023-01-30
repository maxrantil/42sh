/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_reset_fg_grp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:40:51 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/28 16:07:04 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern	t_shell *g_sh;

void	reset_fg_grp()
{
	// if (g_sh->jobs->shared_mem_id > -1 && g_sh->jobs->shared_mem_index > -1)
		// detach_and_remove();
	g_sh->jobs->shared_mem_id = shmget(IPC_PRIVATE, sizeof(int) * 255, IPC_CREAT | 0666);
	g_sh->jobs->shared_mem_index = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
	if (g_sh->jobs->shared_mem_id < 0 || g_sh->jobs->shared_mem_index < 0)
	{
		ft_err_print(NULL, "shmget", "no memory available", 2);
		exit(1);
	}
}
