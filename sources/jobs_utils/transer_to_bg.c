/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transer_to_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:01:18 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/31 17:37:29 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell *g_sh;

static init_pid(t_bg_jobs *bg_node)
{
	int	i;

	i = 0;
	bg_node->pid = (int *)ft_memalloc(sizeof(int) * ft_arrlen(g_sh->fg_job.pid));
	while (g_sh->fg_job.pid[i])
	{
		bg_node->pid[i] = g_sh->fg_job.pid[i];
		i++;
	}
}

static init_cmd(t_bg_jobs *bg_node)
{
	int	i;
	int	j;

	bg_node->cmd = (char ***)ft_memalloc(sizeof(char **) * (ft_arrlen(g_sh->fg_job.cmd) + 1));
	i = 0;
	while (g_sh->fg_job.cmd[i])
	{
		j = 0;
		bg_node->cmd[i] = (char **)ft_memalloc(sizeof(char *) * (ft_arrlen(g_sh->fg_job.cmd[i]) + 1));
		while (g_sh->fg_job.cmd[i][j])
		{
			bg_node->cmd[i][j] = ft_strdup(g_sh->fg_job.cmd[i][j]);
			j++;
		}
		bg_node->cmd[i][j] = NULL;
		i++;
	}
	bg_node->cmd[i] = NULL;
}

static t_bg_jobs	*init_bg_node(int pid, int status, int index)
{
	t_bg_jobs	*bg_node;

	bg_node = (t_bg_jobs *)ft_memalloc(sizeof(t_bg_jobs));
	bg_node->gpid = g_sh->fg_job.gpid;
	init_pid(bg_node);
	init_cmd(bg_node);
	bg_node->status = status;
	bg_node->index = index;
	bg_node->next = NULL;

}

void	transfer_to_bg(int pid, int status)
{
	if (!g_sh->bg_node)
	{
		init_bg_node(pid, status, 0);
		return ;
	}
	while (g_sh->bg_node)
		g_sh->bg_node = g_sh->bg_node->next;
	g_sh->bg_node->next = init_bg_node(pid, status, g_sh->bg_node->index + 1);
}