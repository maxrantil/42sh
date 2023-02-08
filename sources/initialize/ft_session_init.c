/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_session_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:44:03 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/08 14:00:33 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_shell		*g_sh;
t_term		*g_t;

/**
 * It initializes the session struct.
 *
 * @param sh The session struct.
 */
void	ft_session_init(t_shell *sh)
{
	set_signal_keyboard();
	sh->pgid = getpid();
	init_window_size(sh->term);
	sh->ampersand = false;
	g_sh = sh;
	g_t = sh->term;
	sh->jobs = NULL;
	sh->bg_node = NULL;
	sh->process_count = 0;
	sh->exit_stat = 0;
	sh->line = NULL;
	ft_env_init(sh);
	sh->terminal = ttyname(STDOUT_FILENO);
	sh->head = NULL;
	sh->tmp_env_key = NULL;
	sh->tokens = NULL;
	sh->jobs = ft_init_jobs();
	sh->pipe = ft_memalloc(sizeof(t_pipe));
	sh->pipe->pipefd[0] = -1;
	sh->pipe->pipefd[1] = -1;
	sh->pipe->stdincpy = dup(STDIN_FILENO);
	sh->pipe->stdoutcpy = dup(STDOUT_FILENO);
	hash_init(sh);
	sh->is_flag_on = 0;
	sh->option_count = 0;
	ft_init_fg_node(sh);
	sh->exit_confirm = true;
}
