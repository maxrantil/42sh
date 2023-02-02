/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fg_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:51:30 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/02 20:49:56 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	update_fg_job(t_shell *sh, pid_t pid, char **cmd)
{
    if (pid == 0 && sh->ampersand)
        set_process_group(sh, pid);
    else if (pid)
    {
        if (sh->ampersand)
            sh->fg_node->gpid = pid;
        else
            sh->fg_node->gpid = sh->pgid;
        append_pid_arr(sh->fg_node, pid);
        append_cmd_arr(sh->fg_node, cmd);   
    }
}
