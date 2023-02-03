/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_session_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:44:03 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/30 18:58:26 by spuustin         ###   ########.fr       */
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
	sesh->is_flag_on = 0;
	sesh->option_count = 0;
}
