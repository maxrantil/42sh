/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_fg_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:17:41 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/13 11:59:50 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	ft_init_fg_node(t_shell *sh)
{
	sh->fg_node->gpid = 0;
	sh->fg_node->pid = NULL;
	sh->fg_node->cmd = NULL;
}
