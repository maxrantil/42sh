/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_attach_fg_grp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:43:23 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/28 14:45:36 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern	t_shell *g_sh;

/* Attach shared memory array and shared memory index */
void	attach_fg_grp()
{
	if (g_sh->jobs->shared_mem_ptr && g_sh->jobs->shared_mem_idx_ptr)
		detach_fg_grp();
	g_sh->jobs->shared_mem_ptr = (int *)shmat(g_sh->jobs->shared_mem_id, NULL, 0);
	g_sh->jobs->shared_mem_idx_ptr = (int *)shmat(g_sh->jobs->shared_mem_index, NULL, 0);
	if (g_sh->jobs->shared_mem_ptr == (int *)-1 || g_sh->jobs->shared_mem_idx_ptr == (int *)-1)
	{
		ft_err_print(NULL, "shmat", "no memory available", 2);
		exit (1);
	}
}
