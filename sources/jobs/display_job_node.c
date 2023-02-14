/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_job_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:32:14 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/14 15:08:11 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	display_state(t_shell *sh, int status)
{
	char	*str;
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
	ft_putstr_fd("  ", sh->pipe->stdoutcpy);
	ft_putstr_fd(str, sh->pipe->stdoutcpy);
	len = 24 - ft_strlen(str);
	while (--len)
		ft_putstr_fd("  ", sh->pipe->stdoutcpy);
}

static void	print_queue(t_shell *sh, int index)
{
	if (sh->process_queue[0] == index)
		ft_putchar_fd('+', sh->pipe->stdoutcpy);
	else if (sh->process_queue[1] == index)
		ft_putchar_fd('-', sh->pipe->stdoutcpy);
	else
		ft_putchar_fd(' ', sh->pipe->stdoutcpy);
}

void	display_job_node(t_shell *sh, t_bg_jobs *job)
{
	if (job)
	{
		ft_putstr_fd("[", sh->pipe->stdoutcpy);
		ft_putnbr_fd(job->index + 1, sh->pipe->stdoutcpy);
		ft_putstr_fd("]", sh->pipe->stdoutcpy);
		print_queue(sh, job->index);
		display_state(sh, job->status);
		display_pipeline_cmd(sh, job);
	}
}

/**
 * It displays the job's index, the job's pid, the job's status, 
 * and the job's command.
 * 
 * @param sh the shell structure
 * @param job the job to display
 */
void	display_job_pipeline(t_shell *sh, t_bg_jobs *job)
{
	int	i;

	if (job)
	{
		i = -1;
		ft_putstr_fd("[", sh->pipe->stdoutcpy);
		ft_putnbr_fd(job->index + 1, sh->pipe->stdoutcpy);
		ft_putstr_fd("] ", sh->pipe->stdoutcpy);
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
