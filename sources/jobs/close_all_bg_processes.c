/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all_bg_processes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:48:03 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/02 15:48:20 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	close_all_bg_processes(t_shell *sh)
{
	t_bg_jobs	*bg_node;

	bg_node = sh->bg_node;
	while (bg_node)
	{
		killpg(bg_node->gpid, SIGKILL);
		bg_node = bg_node->next;
	}
}
