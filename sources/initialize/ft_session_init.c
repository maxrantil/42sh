/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_session_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:44:03 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/10 16:29:00 by jniemine         ###   ########.fr       */
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
	sh->bg_node = NULL;
	sh->process_count = 0;
	ft_memset(sh->process_queue, -1, sizeof(sh->process_queue));
	sh->exit_stat = 0;
	sh->line = NULL;
	ft_env_init(sh);
	sh->terminal = ttyname(STDOUT_FILENO);
	sh->head = NULL;
	sh->tmp_env_key = NULL;
	sh->tokens = NULL;
	sh->pipe = ft_memalloc(sizeof(t_pipe));
	sh->pipe->write_pipe[0] = -1;
	sh->pipe->write_pipe[1] = -1;
	sh->pipe->pid = -1;
	sh->pipe->stdincpy = dup(STDIN_FILENO);
	sh->pipe->stdoutcpy = dup(STDOUT_FILENO);
	sh->pipe->redir_out = 0;
	sh->pipe->redir_in = 0;
	sh->pipe->new_pipe = 1;
	sh->pipe->piping = 0;
	sh->pipe->pid = 0;
	if(pipe_wrap(sh->pipe->write_pipe) < 0)
		exit(1);
	hash_init(sh);
	sh->is_flag_on = 0;
	sh->option_count = 0;
	ft_init_fg_node(sh);
	sh->exit_confirm = -1;
}
