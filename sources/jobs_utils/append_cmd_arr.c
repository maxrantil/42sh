/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_cmd_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:49:28 by mike_baru         #+#    #+#             */
/*   Updated: 2023/02/01 11:59:13 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static size_t   array_len(char ***arr)
{
    size_t len;

    len = 0;
    while (*(arr + len))
        len++;
    return (len);
}

// static void print_dbl_arr(char **cmd)
// {
// 	int i;

// 	i = -1;
// 	while (cmd[++i])
// 		ft_printf("cmd -> %s\n", cmd[i]);
// }

static char **dup_dbl_pointer(char **cmd)
{
	int     len;
	char	**dup_arr;

	// print_dbl_arr(cmd);
	len = ft_arrlen(cmd);
	dup_arr = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	dup_arr[len] = NULL;
	while (--len >= 0)
		dup_arr[len] = ft_strdup(cmd[len]);
    return (dup_arr);
}

static char ***realloc_cmd(char ***cmd_arr, char **cmd)
{
	char	***new_arr;
	int		len;

	len = array_len(cmd_arr);
	new_arr = (char ***)ft_memalloc(sizeof(char **) * (len + 2));
	new_arr[len + 1] = NULL;
	new_arr[len] = dup_dbl_pointer(cmd);	
	while (--len >= 0)
		new_arr[len] = cmd_arr[len];
	ft_memdel((void **)&cmd_arr);
    return (new_arr);
}

static char ***alloc_cmd(char **cmd)
{
    char    ***cmd_arr;

	cmd_arr = (char ***)ft_memalloc(sizeof(char **) * 2);
	*cmd_arr = dup_dbl_pointer(cmd);
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

