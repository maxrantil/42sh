/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_remove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:10:46 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/21 13:16:02 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	queue_remove(t_shell *sh, t_bg_jobs *process)
{
	int	i;

	i = -1;
	while (++i < sh->process_count)
	{
		if (process->index == sh->process_queue[i])
		{
			ft_memmove(&sh->process_queue[i], &sh->process_queue[i + 1], \
			(sh->process_count - i) * sizeof(int));
			sh->process_count--;
			break ;
		}
	}
}
