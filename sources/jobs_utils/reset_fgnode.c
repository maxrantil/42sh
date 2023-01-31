/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fgnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mike_barutel <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:26:45 by mike_baru         #+#    #+#             */
/*   Updated: 2023/01/31 11:48:33 by mike_baru        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	reset_cmd(char ***cmd)
{
	int		i;
	char	***tofree;

	if (!cmd)
        return ;
    tofree = cmd;
    while (cmd)
    {
        i = -1;
        while ((*cmd)[++i])
            ft_strdel((*cmd)[i]);
        ft_memdel((void **)&(*cmd));
        cmd++;
    }
    ft_memdel((void **)&cmd);
}

void	reset_fgnode(t_shell *sh)
{
    sh->fg_node.gpid = 0;
    if (sh->fg_node.pid)
        ft_memdel((void **)&sh->fg_node.pid);
    sh->fg_node.pid = NULL;
    reset_cmd(sh->fg_node.cmd);
}

