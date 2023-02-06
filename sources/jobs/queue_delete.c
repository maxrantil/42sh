/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:52:35 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/06 16:55:06 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	queue_delete(t_shell *sh, t_bg_jobs *process)
{
	int	i;

	i = 0;
	while (i < sh->process_count)
	{
		if (process->index == sh->process_queue[i])
		{
			ft_memmove(&sh->process_queue[i], &sh->process_queue[i + 1], \
			(sh->process_count - 1 - i) * sizeof(int));
			sh->process_count--;
			break ;
		}
		i++;
	}
}
