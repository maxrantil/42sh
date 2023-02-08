/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_to_fg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:01:10 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/05 12:34:39 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static pid_t	*dup_pid(pid_t *pid)
{
	int		len;
	pid_t	*new_pid;

	len = 0;
	while (pid[len])
		len++;
	new_pid = (pid_t *)ft_memalloc(sizeof(pid_t) * (len + 1));
	new_pid[len] = 0;
	while (--len >= 0)
		new_pid[len] = pid[len];
	return (new_pid);
}

static char	***dup_cmd(char ***cmd)
{
	int		len;
	char	***new_cmd;

	len = triple_ptr_len(cmd);
	new_cmd = (char ***)ft_memalloc(sizeof(char **) * (len + 1));
	new_cmd[len] = NULL;
	while (--len >= 0)
		new_cmd[len] = dup_dbl_ptr(cmd[len]);
	return (new_cmd);
}

void	transfer_to_fg(t_shell *sh, t_bg_jobs *bg_node)
{
	sh->fg_node->gpid = bg_node->gpid;
	sh->fg_node->pid = dup_pid(bg_node->pid);
	sh->fg_node->cmd = dup_cmd(bg_node->cmd);
}
