/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ampersand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:16:39 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/14 15:25:13 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It executes the left side of the tree, then transfers the process to the 
 * background, then executes the right side of the tree with the ampersand
 * flag set to true.
 * 
 * @param head the head of the tree
 * @param environ_cp a copy of the environment
 * @param terminal the name of the terminal
 * @param sh the shell struct
 */
void	exec_ampersand(t_ampersand *head, char ***environ_cp, \
char *terminal, t_shell *sh)
{
	sh->ampersand = true;
	exec_tree((((t_ampersand *)head)->left), environ_cp, terminal, sh);
	transfer_to_bg(sh, RUNNING);
	display_bg_job(sh);
	reset_fgnode(sh);
	sh->ampersand = false;
	exec_tree((((t_ampersand *)head)->right), environ_cp, terminal, sh);
	reset_fd(sh);
}
