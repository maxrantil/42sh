/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:54 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/02 16:23:15 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

// int	ft_jobs(t_shell *sh)
// {
// 	t_bg_jobs *job;
// 	pid_t	*tmp;
// 	char	***ptr;
// 	char	**dbl;

// 	job = sh->bg_node;
// 	while (job)
// 	{
// 		ft_printf("index %d\n", job->index);
// 		ft_printf("status %d\n", job->status);
// 		ft_printf("gpid %d\n", job->gpid);
// 		tmp = job->pid;
// 		while (tmp && *tmp)
// 			ft_printf("pid: %d\n", *(tmp++));
// 		ptr = job->cmd;
// 		while (ptr && *ptr)
// 		{
// 			dbl = *ptr;
// 			while (*dbl)
// 			{
// 				ft_printf("cmd: %s\n", *dbl);
// 				dbl++;
// 			}
// 			ptr++;
// 		}
// 		job = job->next;
// 	}
// 	return (0);
// }

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

static void	display_process_node(t_bg_jobs *job)
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
		{
			ft_print_dbl_array(*(cmd++));
			if (*(cmd))
				ft_putstr(" | ");
		}
// 	reset_fgnode(g_sh);
		ft_printf(" &\n");
	}
	if (job->status == DONE)
		bg_node_delete(g_sh, &job);

}

int	ft_jobs(t_shell *sh)
{
	t_bg_jobs *job;

	job = sh->bg_node;
	while (job)
	{
		// ft_printf("gpid %d| ", job->gpid);
        display_process_node(job);
		job = job->next;
	}
	return (0);
}
