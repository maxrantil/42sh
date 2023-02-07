/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_info_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:49:07 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/03 14:33:56 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static t_bg_jobs *get_latest_job(t_shell *sh)
{
    t_bg_jobs   *ptr;

    ptr = sh->bg_node;
    while (ptr->next)
        ptr = ptr->next;
    return (ptr);
}

void    display_bg_job(t_shell *sh)
{
    t_bg_jobs   *ptr;

    ptr = get_latest_job(sh);
    ft_printf("[%d] %d\n", ptr->index + 1, ptr->gpid);
}

void    display_suspended_job(t_shell *sh) // This needs to updated
{
    t_bg_jobs   *ptr;
    char        ***cmd;

    ptr = get_latest_job(sh);
    ft_printf("\n[%d]%c  Stopped      ", ptr->index + 1, '+');
    cmd = ptr->cmd;
    while (*cmd)
        ft_print_dbl_array(*(cmd++));
    ft_putchar('\n');
}

void    display_pipeline_cmd(t_bg_jobs *job)
{
    char ***cmd;

    cmd = job->cmd;
    while (*cmd)
    {
        ft_print_dbl_array(*(cmd++));
        if (*(cmd))
            ft_putstr(" | ");
    }
    ft_printf(" &\n");
}
