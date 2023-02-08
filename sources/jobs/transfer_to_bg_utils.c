/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_to_bg_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:32:17 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/07 16:33:06 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	delete_from_queue(t_shell *sh, t_bg_jobs *process)
{
	int	i;

	i = -1;
	while (++i < sh->process_count)
	{
		if (process->index == sh->process_queue[i])
		{
			ft_memmove(&sh->process_queue[i], &sh->process_queue[i + 1], \
			(sh->process_count - 1 - i) * sizeof(int));
			sh->process_count--;
			break ;
		}
	}
}

void	init_pid(t_shell *sh, t_bg_jobs *bg_node)
{
	int	len;

	len = 0;
	while (sh->fg_node->pid[len])
		len++;
	bg_node->pid = (pid_t *)ft_memalloc(sizeof(pid_t) * (len + 1));
	bg_node->pid[len] = 0;
	while (--len >= 0)
		bg_node->pid[len] = sh->fg_node->pid[len];
}

void	init_cmd(t_shell *sh, t_bg_jobs *bg_node)
{
	int	len;

	len = triple_ptr_len(sh->fg_node->cmd);
	bg_node->cmd = (char ***)ft_memalloc(sizeof(char **) * (len + 1));
	bg_node->cmd[len] = NULL;
	while (--len >= 0)
		bg_node->cmd[len] = dup_dbl_ptr(sh->fg_node->cmd[len]);
}

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
	ft_memmove(&sh->process_queue[i + 1], \
	&sh->process_queue[i], (sh->process_count - 1) * sizeof(int));
	sh->process_queue[i] = index;
}
