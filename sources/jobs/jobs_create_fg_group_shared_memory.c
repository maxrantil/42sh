/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_create_fg_group_shared_memory.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:37:48 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/30 15:41:32 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern	t_shell *g_sh;

void	create_fg_grp_memory()
{
	g_sh->jobs->shared_mem_id = create_fg_group_shared_memory(sizeof(int) * 255);
	g_sh->jobs->shared_mem_index = create_fg_group_shared_memory(sizeof(int));
}
