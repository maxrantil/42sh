/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_to_bg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:01:18 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/01 14:49:57 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void init_pid(t_shell *sh, t_bg_jobs *bg_node)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (sh->fg_node->pid[len])
		len++;
	bg_node->pid = (pid_t *)ft_memalloc(sizeof(pid_t) * (len + 1));
	bg_node->pid[len] = 0;
	while (--len >= 0)
		bg_node->pid[len] = sh->fg_node->pid[len];
}

static void init_cmd(t_shell *sh, t_bg_jobs *bg_node)
{
	int	len;

	len = triple_ptr_len(sh->fg_node->cmd);
	bg_node->cmd = (char ***)ft_memalloc(sizeof(char **) * (len + 1));
	bg_node->cmd[len] = NULL;
	while (--len >= 0)
		bg_node->cmd[len] = dup_dbl_ptr(sh->fg_node->cmd[len]);
}

static t_bg_jobs	*init_bg_node(t_shell *sh, int status, int index)
{
	t_bg_jobs	*bg_node;

	bg_node = (t_bg_jobs *)ft_memalloc(sizeof(t_bg_jobs));
	bg_node->gpid = sh->fg_node->gpid;
	init_pid(sh, bg_node);
	init_cmd(sh, bg_node);
	bg_node->status = status;
	bg_node->index = index;
	bg_node->next = NULL;
	return (bg_node);
}

void	transfer_to_bg(t_shell *sh, int status)
{
	if (!sh->bg_node)
	{
		sh->bg_node = init_bg_node(sh, status, 0);
		return ;
	}
	// while (sh->bg_node)
	// 	sh->bg_node = g_sh->bg_node->next;
	// sh->bg_node->next = init_bg_node(pid, status, g_sh->bg_node->index + 1);
}
