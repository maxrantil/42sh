/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:03:43 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/06 13:30:30 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int ft_bg(t_shell *sh, char **cmd)
{
		t_bg_jobs   *job;

		job = bg_fetch_node(sh, *(cmd + 1));
		if (!job)
		ft_putstr("fg: no such job\n");
		else
		{
				ft_print_dbl_array(*job->cmd);
				ft_putchar('\n');
				if (job->status == STOPPED || job->status == SUSPENDED)
				{
						job->status = RUNNING;
						killpg(job->gpid, SIGCONT);
				}
				else
						ft_err_print(NULL, "bg", "job already in the background", 2);
		}
		return (0);
}
