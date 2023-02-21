/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_move_to_front.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:56:50 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/21 13:16:20 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	queue_move_to_front(t_shell *sh, t_bg_jobs *job)
{
	queue_remove(sh, job);
	sh->process_count++;
	ft_memmove(&sh->process_queue[1], \
	&sh->process_queue[0], sh->process_count * sizeof(int));
	sh->process_queue[0] = job->index;
}
