/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_job.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:05:12 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/01 18:16:59 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

static void	display_state(int status)
{
	if (status == DONE)
		ft_printf("%2s%-24s", "", "Done");
	else if (status == STOPPED)
		ft_printf("%2s%-24s", "", "Stopped");
	else if (status == TERMINATED)
		ft_printf("%2s%-24s", "", "Terminated");
	else if (status == SUSPENDED)
		ft_printf("%2s%-24s", "", "Suspended");
	else
		ft_printf("%2s%-24s", "", "Running");
}

static void	print_queue(int index)
{
	if (g_sh->process_queue[0] == index)
		ft_putchar('+');
	else if (g_sh->process_queue[1] == index)
		ft_putchar('-');
	else
		ft_putchar(' ');
}

void	display_process_node(t_bg_jobs *job)
{
	char	***cmd;

	cmd = NULL;
	if (job)
	{
		ft_printf("[%d]", job->index + 1);
		print_queue(job->index);
		display_state(job->status);
		cmd = job->cmd;
		while (*cmd)
			ft_print_dbl_array(*(cmd++));
		ft_printf("\n");
	}
	if (job->status == DONE)
		bg_node_delete(g_sh, &job);

}
