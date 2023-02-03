/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_logicalop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:00:00 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/03 01:44:57 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	exe_logical_or(t_logicalop *logicalop, char ***environ_cp, \
		char *terminal, t_shell *sh);

/* If exit_stat = 0 execute, if next one is and call this recursively, else if next one is or call it, else call exec_tree*/
static void	exe_logical_and(t_logicalop *logicalop, char ***environ_cp, \
		char *terminal, t_shell *sh)
{
	ft_printf("exe_logical_and\n");
	if (sh->exit_stat == 0)
		exec_tree(logicalop->left, environ_cp, terminal, sh);
	else if (logicalop->right && logicalop->right->type == LOGICAL_AND)
		exe_logical_and(((t_logicalop *)logicalop->right), environ_cp, terminal, sh);
	else if (logicalop->right && logicalop->right->type == LOGICAL_OR)
		exe_logical_or(((t_logicalop *)logicalop->right), environ_cp, terminal, sh);
	else
		exec_tree(logicalop->right, environ_cp, terminal, sh);
}

/* If exit_stat = 1 execute this, if next one is redir, call this recursively with it, if next one is and call logical_and. If anything else, call exec tree*/
static void	exe_logical_or(t_logicalop *logicalop, char ***environ_cp, \
		char *terminal, t_shell *sh)
{
	ft_printf("exe_logical_or\n");
	if (sh->exit_stat == 1)
		exec_tree(logicalop->left, environ_cp, terminal, sh);
	else if (logicalop->right && logicalop->right->type == REDIR)
		exe_logical_or(((t_logicalop *)logicalop->right), environ_cp, terminal, sh);
	else if (logicalop->right && logicalop->right->type == LOGICAL_OR)
		exe_logical_and(((t_logicalop *)logicalop->right), environ_cp, terminal, sh);
	else
		exec_tree(logicalop->right, environ_cp, terminal, sh);
}

void	exec_logicalop(t_logicalop *logicalop, char ***environ_cp, \
		char *terminal, t_shell *sh)
{
	exec_tree(logicalop->left, environ_cp, terminal, sh);
	if (logicalop->right && logicalop->right->type == LOGICAL_AND)
		exe_logical_and(((t_logicalop *)logicalop->right), environ_cp, terminal, sh);
	else if (logicalop->right && logicalop->right->type == LOGICAL_OR)
		exe_logical_or(((t_logicalop *)logicalop->right), environ_cp, terminal, sh);
	else
		exec_tree(logicalop->right, environ_cp, terminal, sh);
}
