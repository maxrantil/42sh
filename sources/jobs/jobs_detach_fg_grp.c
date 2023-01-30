/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_detach_fg_grp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:24:38 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/29 22:24:38 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell *g_sh;

/* Detach foreground group from shared memory */
void	detach_fg_grp(void)
{
	if (!g_sh->jobs->shared_mem_ptr || !g_sh->jobs->shared_mem_idx_ptr)
		return ;
	if (shmdt(g_sh->jobs->shared_mem_ptr) < 0 || shmdt(g_sh->jobs->shared_mem_idx_ptr) < 0)
	{
		ft_err_print(NULL, "shmdt", "failed to detach from shared memory", 2);
		exit (1);
	}
	g_sh->jobs->shared_mem_ptr = NULL;
	g_sh->jobs->shared_mem_idx_ptr = NULL;
}
