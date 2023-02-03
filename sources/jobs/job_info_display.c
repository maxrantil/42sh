/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_info_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:49:07 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/03 12:58:17 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void    display_bg_job(t_shell *sh)
{
    t_bg_jobs   *ptr;

    ptr = sh->bg_node;
    while (ptr->next)
        ptr = ptr->next;
    ft_printf("[%d] %d\n", ptr->index + 1, ptr->gpid);
}
