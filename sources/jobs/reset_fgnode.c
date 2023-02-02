/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fgnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:26:45 by mike_baru         #+#    #+#             */
/*   Updated: 2023/02/02 16:20:44 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	reset_fgnode(t_shell *sh)
{
    sh->fg_node->gpid = 0;
	if (sh->fg_node->pid)
		ft_memdel((void **)&sh->fg_node->pid);
	if (sh->fg_node->cmd)
		reset_cmd(&sh->fg_node->cmd);
}

