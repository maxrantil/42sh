/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_detach_and_remove_fg_grp.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:35:51 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/28 16:34:22 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern	t_shell *g_sh;

void delete_fg_group_shared_memory(void)
{
	if (shmctl(g_sh->jobs->shared_mem_id, IPC_RMID, NULL) < 0 || shmctl(g_sh->jobs->shared_mem_index, IPC_RMID, NULL) < 0)
	{
		ft_err_print(NULL, "shmctk", "failed to delete shared memory", 2);
		exit (1);
	}
	g_sh->jobs->shared_mem_id = -1;
	g_sh->jobs->shared_mem_index = -1;
}

void detach_and_remove(void)
{
	detach_fg_grp();
	delete_fg_group_shared_memory();
}
