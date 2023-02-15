/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_info_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:49:07 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/14 15:08:55 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	ft_print_dbl_array_fd(char **cmd, int fd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1])
			ft_putstr_fd(" ", fd);
	}
}

static t_bg_jobs	*get_latest_job(t_shell *sh)
{
	t_bg_jobs	*ptr;

	ptr = sh->bg_node;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void	display_bg_job(t_shell *sh)
{
	t_bg_jobs	*ptr;

	ptr = get_latest_job(sh);
	ft_putstr_fd("[", sh->pipe->stdoutcpy);
	ft_putnbr_fd(ptr->index + 1, sh->pipe->stdoutcpy);
	ft_putstr_fd("] ", sh->pipe->stdoutcpy);
	ft_putnbr_fd(ptr->gpid, sh->pipe->stdoutcpy);
	ft_putstr_fd("\n", sh->pipe->stdoutcpy);
}

void	display_suspended_job(t_shell *sh, int pid)
{
	t_bg_jobs	*ptr;

	ptr = sh->bg_node;
	while (ptr)
	{
		if (ptr->gpid == pid)
			break ;
		ptr = ptr->next;
	}
	if (ptr)
	{
		ft_putstr_fd("\n", sh->pipe->stdoutcpy);
		display_job_node(sh, ptr);
	}
}

/**
 * It displays the pipeline command in the shell's stdout
 * 
 * @param sh the shell structure
 * @param job the job to display
 */
void	display_pipeline_cmd(t_shell *sh, t_bg_jobs *job)
{
	char	***cmd;

	cmd = job->cmd;
	while (*cmd)
	{
		ft_print_dbl_array_fd(*(cmd++), sh->pipe->stdoutcpy);
		if (*(cmd))
			ft_putstr_fd(" | ", sh->pipe->stdoutcpy);
	}
	ft_putstr_fd(" &\n", sh->pipe->stdoutcpy);
}
