/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fg_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/10 00:18:48 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_42sh.h"

void	update_fg_job(t_shell *sh, pid_t pid, char **cmd)
{
	set_process_group(sh, pid);
	append_pid_arr(sh->fg_node, pid);
	append_cmd_arr(sh->fg_node, cmd);
}
