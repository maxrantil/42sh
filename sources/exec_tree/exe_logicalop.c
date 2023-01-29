/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_logicalop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:00:00 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/27 15:08:00 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	exe_logical_and(t_logicalop *logicalop, char ***environ_cp,
		char *terminal, t_shell *sh)
{
	exec_tree(logicalop->left, environ_cp, terminal, sh);
	if (logicalop->right && logicalop->right->type == LOGICAL_OR)
		exec_tree(logicalop->right, environ_cp, terminal, sh);
}

static void	exe_logical_or(t_logicalop *logicalop, char ***environ_cp,
		char *terminal, t_shell *sh)
{
	if (sh->exit_stat == 0)
		exec_tree(logicalop->left, environ_cp, terminal, sh);
	else if (logicalop->right && logicalop->right->type == CMD)
		exec_tree(logicalop->right, environ_cp, terminal, sh);
}

void	exec_logicalop(t_logicalop *logicalop, char ***environ_cp,
		char *terminal, t_shell *sh)
{
	if (logicalop->type == LOGICAL_AND)
		exe_logical_and(logicalop, environ_cp, terminal, sh);
	else if (logicalop->type == LOGICAL_OR)
		exe_logical_or(logicalop, environ_cp, terminal, sh);
}
