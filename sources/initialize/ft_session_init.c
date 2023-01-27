/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:44:03 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/26 09:55:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_shell	*g_session;
t_term		*g_t;

/**
 * It initializes the session struct.
 *
 * @param sh The session struct.
 */
void	ft_session_init(t_shell *sh)
{
	init_window_size(sh->term);
	g_session = sh;
	g_t = sh->term;
	sh->exit_stat = 0;
	sh->line = NULL;
	ft_env_init(sh);
	sh->terminal = ttyname(STDOUT_FILENO);
	sh->head = NULL;
	sh->tmp_env_key = NULL;
	sh->tokens = NULL;
	sh->shared_mem_id = -1;
	sh->shared_mem_index = -1;
	hash_init(sh);
}
