/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_job_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:32:14 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/12 18:15:25 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	display_state(t_shell *sh, int status)
{
	char 	*str;
	int		len;

	if (status == DONE)
		str = "Done";
	else if (status == STOPPED)
		str = "Stopped";
	else if (status == TERMINATED)
		str = "Terminated";
	else if (status == SUSPENDED)
		str = "Suspended";
	else if (status == EXITED)
		str = "Exited";
	else
		str = "Running";
	
	ft_putstr_fd("  ", sh->pipe->stdincpy);
	ft_putstr_fd(str, sh->pipe->stdincpy);
	len = 24 - ft_strlen(str);
	while (--len)
		ft_putstr_fd("  ", sh->pipe->stdincpy);
}

static void	print_queue(t_shell *sh, int index)
{
	if (sh->process_queue[0] == index)
		ft_putchar_fd('+', sh->pipe->stdincpy);
	else if (sh->process_queue[1] == index)
		ft_putchar_fd('-', sh->pipe->stdincpy);
	else
		ft_putchar_fd(' ', sh->pipe->stdincpy);
}

void	display_job_node(t_shell *sh, t_bg_jobs *job)
{
	if (job)
	{
		ft_putstr_fd("[", sh->pipe->stdincpy);
		ft_putnbr_fd(job->index + 1, sh->pipe->stdincpy);
		ft_putstr_fd("] ", sh->pipe->stdincpy);
		print_queue(sh, job->index);
		display_state(sh, job->status);
		display_pipeline_cmd(sh, job);
	}
}

void	display_job_pipeline(t_shell *sh, t_bg_jobs *job)
{
	int	i;
	
	if (job)
	{
		i = -1;
		ft_putstr_fd("[", sh->pipe->stdincpy);
		ft_putnbr_fd(job->index + 1, sh->pipe->stdincpy);
		ft_putstr_fd("] ", sh->pipe->stdincpy);
		print_queue(sh, job->index);
		ft_printf(" %d ", job->pid[++i]);
		display_state(sh, job->status);
		ft_print_dbl_array(job->cmd[i]);
		ft_putchar('\n');
		while (job->pid[++i])
		{
			ft_printf("%5s%d  ", "", job->pid[i]);
			ft_printf("%23s| ", "");
			ft_print_dbl_array(job->cmd[i]);
			ft_putchar('\n');
		}
	}
}
