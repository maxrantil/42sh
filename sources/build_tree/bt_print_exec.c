/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_print_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:32:28 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/26 09:55:22 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	print_exec(t_treenode *node)
{
	size_t		len;
	t_cmdnode	*root;

	root = (t_cmdnode *)node;
	len = ft_arrlen(root->cmd);
	ft_printf("exec ");
	if (len > 2)
		ft_printf("[%s] [1]%s [2]%s [3]%s\n", root->cmd[0], \
		root->cmd[1], root->cmd[2], root->cmd[3]);
	else if (len == 2)
		ft_printf("[%s] %s\n", root->cmd[0], root->cmd[1]);
	else
		ft_printf("[%s]\n", root->cmd[0]);
}
