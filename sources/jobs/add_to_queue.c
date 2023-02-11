/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:09:39 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/11 18:22:47 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	add_to_queue(t_shell *sh, int index)
{
	int			i;
	t_bg_jobs	*tmp;

	i = 0;
	tmp = sh->bg_node;
	while (tmp)
	{
		if (tmp->index == sh->process_queue[i])
		{
			if (tmp->status == STOPPED)
			{
				i++;
				tmp = sh->bg_node;
			}
		}
		tmp = tmp->next;
	}
	++sh->process_count;
	ft_memmove(&sh->process_queue[i + 1], \
	&sh->process_queue[i], sh->process_count * sizeof(int));
	sh->process_queue[i] = index;
}
