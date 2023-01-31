/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fgnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:26:45 by mike_baru         #+#    #+#             */
/*   Updated: 2023/01/31 20:44:34 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	reset_cmd(char ***cmd)
{
	int		i;
	char	***tofree;

    tofree = cmd;
    while (cmd)
    {
        i = -1;
        while ((*cmd)[++i])
            ft_strdel(&(*cmd)[i]);
        ft_memdel((void **)&(*cmd));
        cmd++;
    }
    ft_memdel((void **)&tofree);
}

void	reset_fgnode(t_shell *sh)
{
	ft_printf("THIS HAPPENS");
    sh->fg_node->gpid = 0;
    if (sh->fg_node->pid)
        ft_memdel((void **)&sh->fg_node->pid);
	else
		sh->fg_node->pid = NULL;
	if (sh->fg_node->cmd)
		reset_cmd(sh->fg_node->cmd);
	else
		sh->fg_node->cmd = NULL;
}

void	init_fgnode(t_shell *sh)
{
    sh->fg_node->gpid = 0;
	sh->fg_node->pid = NULL;
	sh->fg_node->cmd = NULL;
}
