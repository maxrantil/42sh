/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_cmd_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:49:28 by mike_baru         #+#    #+#             */
/*   Updated: 2023/02/01 14:27:33 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// static void print_dbl_arr(char **cmd)
// {
// 	int i;

// 	i = -1;
// 	while (cmd[++i])
// 		ft_printf("cmd -> %s\n", cmd[i]);
// }

static char ***realloc_cmd(char ***cmd_arr, char **cmd)
{
	char	***new_arr;
	int		len;

	len = triple_ptr_len(cmd_arr);
	new_arr = (char ***)ft_memalloc(sizeof(char **) * (len + 2));
	new_arr[len + 1] = NULL;
	new_arr[len] = dup_dbl_ptr(cmd);	
	while (--len >= 0)
		new_arr[len] = cmd_arr[len];
	ft_memdel((void **)&cmd_arr);
    return (new_arr);
}

static char ***alloc_cmd(char **cmd)
{
    char    ***cmd_arr;

	cmd_arr = (char ***)ft_memalloc(sizeof(char **) * 2);
	*cmd_arr = dup_dbl_ptr(cmd);
    *(cmd_arr + 1) = NULL;
    return(cmd_arr);
}

void	append_cmd_arr(t_fg_job *fg_node, char **cmd)
{
	if (!fg_node->cmd)
		fg_node->cmd = alloc_cmd(cmd);
    else
		fg_node->cmd = realloc_cmd(fg_node->cmd, cmd);
}

