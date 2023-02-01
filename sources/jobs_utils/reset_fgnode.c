/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fgnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:26:45 by mike_baru         #+#    #+#             */
/*   Updated: 2023/02/01 10:50:09 by mike_baru        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	reset_cmd(char ****cmd)
{
	char	***tofree;

    tofree = *cmd;
    while (*tofree)
    {
        ft_arrclean(*tofree);
        ++tofree;
    }
    ft_memdel((void **)&(*cmd));
}

void	reset_fgnode(t_shell *sh)
{
    sh->fg_node->gpid = 0;
	if (sh->fg_node->pid)
		ft_memdel((void **)&sh->fg_node->pid);
	if (sh->fg_node->cmd)
		reset_cmd(&sh->fg_node->cmd);
}

void	init_fgnode(t_shell *sh)
{
    sh->fg_node->gpid = 0;
	sh->fg_node->pid = NULL;
	sh->fg_node->cmd = NULL;
}