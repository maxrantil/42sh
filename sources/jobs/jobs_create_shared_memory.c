/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_create_shared_memory.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:40:51 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/30 15:39:20 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern	t_shell *g_sh;

int		create_fg_group_shared_memory(size_t size)
{
	int		shm_id;

	shm_id = shmget(IPC_PRIVATE, size, IPC_CREAT | 0666);
	if (shm_id < 0)
	{
		ft_err_print(NULL, "shmget", "no memory available", 2);
		exit(1);
	}
	return (shm_id);
}
