/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_session_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:44:03 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/25 16:16:22 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_session	*g_session;
t_term		*g_t;

/**
 * It initializes the session struct.
 *
 * @param sesh The session struct.
 */
void	ft_session_init(t_session *sesh)
{
	init_window_size(sesh->term);
	g_session = sesh;
	g_t = sesh->term;
	sesh->exit_stat = 0;
	sesh->line = NULL;
	ft_env_init(sesh);
	sesh->terminal = ttyname(STDOUT_FILENO);
	sesh->head = NULL;
	sesh->tmp_env_key = NULL;
	sesh->tokens = NULL;
	hash_init(sesh);
}
