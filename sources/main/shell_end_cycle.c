/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_end_cycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:26:23 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/13 11:29:14 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	ft_reset_tmp_env(t_shell *sh)
{
	int		i;
	char	*key;
	char	**env;

	i = -1;
	if (sh->tmp_env_key)
	{
		while (sh->tmp_env_key[++i])
		{
			key = ft_strchr(sh->tmp_env_key[i], '=');
			if (key)
			{
				key = ft_strsub(sh->tmp_env_key[i], 0, key - \
					sh->tmp_env_key[i]);
				env = ft_env_get(sh, key, sh->env);
				ft_strdel(env);
				*env = ft_strdup(sh->tmp_env_key[i]);
				ft_strdel(&key);
			}
			else
				ft_env_remove(sh, sh->tmp_env_key[i]);
			ft_strdel(&sh->tmp_env_key[i]);
		}
		ft_memdel((void **)&sh->tmp_env_key);
	}
}

static void    notify_completed_jobs(t_shell *sh)
{
    t_bg_jobs    *ptr;

    ptr = sh->bg_node;
    while (ptr)
    {
		if (ptr->status == DONE || ptr->status == TERMINATED || ptr->status == EXITED)
		{
            display_job_node(sh, ptr);
			bg_node_delete(sh, &ptr);
		}
		else
			ptr = ptr->next;
    }
}

/**
 * It resets the tokens and sets the return value to 0
 *
 * @param sh the session struct
 */
void	shell_end_cycle(t_shell *sh)
{

	free_node(sh->head);
	free_tokens(&sh->tokens);
	reset_fd(sh);
	sh->pipe->stdincpy = dup(STDIN_FILENO);
	sh->pipe->stdoutcpy = dup(STDOUT_FILENO);
	sh->pipe->redir_out = 0;
	sh->pipe->redir_in = 0;
	sh->pipe->piping = 0;
	ft_memset(sh->pipe->fd_aliases, -1, sizeof(int) * SH_FD_MAX);
	while(ioctl(sh->pipe->stdincpy, TIOCSPGRP, &sh->pgid) == -1)
		ft_putstr_fd("ioctl error", 2);
	ft_reset_tmp_env(sh);
	notify_completed_jobs(sh);
	init_window_size(sh->term);
	reset_fgnode(sh);
}
