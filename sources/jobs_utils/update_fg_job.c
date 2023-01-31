/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fg_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:51:30 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/31 18:15:36 by mike_baru        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

//void	update_fg_job(t_shell *sh, pid_t pid, char **cmd)
void	update_fg_job(t_shell *sh, pid_t pid)
{
//	set_process_group(sh, pid);
	ft_printf("THIS HAPPENS\n");
	append_pid_arr(sh->fg_node, pid);
//	append_cmd_arr(sh->fg_node, cmd);
}
