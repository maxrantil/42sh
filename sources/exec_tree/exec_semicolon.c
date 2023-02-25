/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_semicolon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:24:40 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/25 03:14:58 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It executes the left side of the semicolon, then the right side.
 *
 * @param head the head of the tree
 * @param environ_cp a copy of the environment
 * @param terminal the name of the terminal
 * @param sh the shell structure
 */
void	exec_semicolon(t_semicolon *head, char ***environ_cp, \
char *terminal, t_shell *sh)
{
	exec_tree((((t_semicolon *)head)->left), environ_cp, terminal, sh);
	sh->pipe->redir_in = 0;
	sh->pipe->redir_out = 0;
	reset_fd(sh);
	if (head && ((t_semicolon *)head)->right)
		exec_tree((((t_semicolon *)head)->right), environ_cp, terminal, sh);
	reset_fd(sh);
	sh->pipe->redir_in = 0;
	sh->pipe->redir_out = 0;
}
