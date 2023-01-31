/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_cmd_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mike_barutel <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:49:28 by mike_baru         #+#    #+#             */
/*   Updated: 2023/01/31 17:08:30 by mike_baru        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	realloc_cmd(char ***cmd_arr, char **cmd)
{
	pid_t	*new_arr;
	int		len;

	len = 0;
	while ((*pid_arr) + len)
		++len;
	new_arr = (pid_t *)ft_memalloc(sizeof(pid_t) * (len + 2));
	new_arr[len--] = NULL;
	new_arr[len--] = pid;	
	while (len)
		new_arr[len] = (*pid_arr)[len--];
	ft_memdel((void **)&(*pid_arr));
	*pid_arr = new_arr;
}

static char **dup_dbl_pointer(char **cmd)
{
	int	len;
	int	dup_arr;

	len = ft_arrlen(cmd);
	dup_arr = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	dup_arr[len] = NULL;
	while (--len)
		dup_arr[len] = ft_strdup(cmd[len]);
}

static void alloc_cmd(char ***cmd_arr, char **cmd)
{
	cmd_arr = (char ***)ft_memalloc(sizeof(char **cmd) * 2);
	*cmd_arr = dup_dbl_pointer(cmd);
	(*cmd_arr) + 1 = NULL;
}

void	append_cmd_arr(t_fgnode fg_node, char **cmd)
{
	if (!fg_node.cmd)
		alloc_cmd(fg_node.cmd, cmd);
	else
		realloc_cmd(fg_node.cmd, cmd);
}

