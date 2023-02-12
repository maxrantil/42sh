/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_to_bg_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:32:17 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/11 18:10:56 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	init_pid(t_shell *sh, t_bg_jobs *bg_node)
{
	int	len;

	len = 0;
	while (sh->fg_node->pid && sh->fg_node->pid[len])
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
