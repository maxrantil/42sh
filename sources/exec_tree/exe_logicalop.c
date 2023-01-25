/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_logicalop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:00:00 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/12 19:21:51 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	exe_logical_and(t_logicalop *logicalop, char ***environ_cp,
		char *terminal, t_session *sesh)
{
	exec_tree(logicalop->left, environ_cp, terminal, sesh);
	if (sesh->exit_stat == 0)
		exec_tree(logicalop->right, environ_cp, terminal, sesh);
}

static void	exe_logical_or(t_logicalop *logicalop, char ***environ_cp,
		char *terminal, t_session *sesh)
{
	exec_tree(logicalop->left, environ_cp, terminal, sesh);
	if (sesh->exit_stat != 0)
		exec_tree(logicalop->right, environ_cp, terminal, sesh);
}

void	exec_logicalop(t_logicalop *logicalop, char ***environ_cp,
		char *terminal, t_session *sesh)
{
	if (logicalop->type == LOGICAL_AND)
		exe_logical_and(logicalop, environ_cp, terminal, sesh);
	else if (logicalop->type == LOGICAL_OR)
		exe_logical_or(logicalop, environ_cp, terminal, sesh);
}
