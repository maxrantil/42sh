/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_logicalop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:00:00 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/14 15:55:33 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	exe_logical_or(t_logicalop *logicalop, char ***environ_cp, \
		char *terminal, t_shell *sh);

/*	If exit_stat of the last one has been 0, it has been successfull,
	and we execute this one, after that we call the proper function */
static void	exe_logical_and(t_logicalop *logicalop, char ***environ_cp, \
		char *terminal, t_shell *sh)
{
	if (sh->exit_stat == 0)
		exec_tree(logicalop->left, environ_cp, terminal, sh);
	if (logicalop->right && logicalop->right->type == LOGICAL_AND)
		exe_logical_and(((t_logicalop *)logicalop->right), \
		environ_cp, terminal, sh);
	else if (logicalop->right && logicalop->right->type == LOGICAL_OR)
		exe_logical_or(((t_logicalop *)logicalop->right), \
		environ_cp, terminal, sh);
	else
		exec_tree(logicalop->right, environ_cp, terminal, sh);
}

/*	
If exit_stat of the last one has been other than 0, it has failed,
and we execute this one, after that we call the proper function 
*/
static void	exe_logical_or(t_logicalop *logicalop, char ***environ_cp, \
		char *terminal, t_shell *sh)
{
	if (sh->exit_stat != 0)
		exec_tree(logicalop->left, environ_cp, terminal, sh);
	if (logicalop->right && logicalop->right->type == LOGICAL_OR)
		exe_logical_or(((t_logicalop *)logicalop->right), \
		environ_cp, terminal, sh);
	else if (logicalop->right && logicalop->right->type == LOGICAL_AND)
		exe_logical_and(((t_logicalop *)logicalop->right), \
		environ_cp, terminal, sh);
	else
		exec_tree(logicalop->right, environ_cp, terminal, sh);
}

/*
First we execute the head, then we call either another of the recurisve
functions exe_logcical_and or exe_logical_or. If there is no more following
logical operators we return to exec_tree.
*/
void	exec_logicalop(t_logicalop *logicalop, char ***environ_cp, \
		char *terminal, t_shell *sh)
{
	exec_tree(logicalop->left, environ_cp, terminal, sh);
	if (logicalop->right && logicalop->right->type == LOGICAL_AND)
		exe_logical_and(((t_logicalop *)logicalop->right), \
		environ_cp, terminal, sh);
	else if (logicalop->right && logicalop->right->type == LOGICAL_OR)
		exe_logical_or(((t_logicalop *)logicalop->right), \
		environ_cp, terminal, sh);
	else
		exec_tree(logicalop->right, environ_cp, terminal, sh);
}
