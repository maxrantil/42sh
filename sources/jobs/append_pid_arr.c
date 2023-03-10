/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_pid_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:12:46 by mike_baru         #+#    #+#             */
/*   Updated: 2023/02/10 01:23:43 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static pid_t	*realloc_pid(pid_t **pid_arr, pid_t pid)
{
	pid_t	*new_arr;
	int		len;

	len = 0;
	while (*(*pid_arr + len))
		++len;
	new_arr = (pid_t *)ft_memalloc(sizeof(pid_t) * (len + 2));
	new_arr[len + 1] = 0;
	new_arr[len] = pid;
	while (--len >= 0)
		new_arr[len] = (*pid_arr)[len];
	ft_memdel((void **)&(*pid_arr));
	return (new_arr);
}

static pid_t	*alloc_pid(pid_t pid)
{
	pid_t	*pid_arr;

	pid_arr = (pid_t *)ft_memalloc(sizeof(pid_t) * 2);
	*pid_arr = pid;
	*(pid_arr + 1) = 0;
	return (pid_arr);
}

void	append_pid_arr(t_fg_job *fg_node, pid_t pid)
{
	if (!fg_node->pid)
		fg_node->pid = alloc_pid(pid);
	else
		fg_node->pid = realloc_pid(&fg_node->pid, pid);
}
