/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:31:23 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/16 15:39:26 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	close_fd(int *fd, int limit)
{
	while (*fd >= limit)
	{
		close(*fd);
		--(*fd);
	}
}

static void	open_fd(t_shell *sh, int *fd)
{
	*fd = 0;
	while (*fd <= SH_FD_MAX)
	{
		open(sh->terminal, O_RDWR);
		++(*fd);
	}
}

void	reset_fd(t_shell *sh)
{
	int		fd;

	fd = SH_FD_MAX;
	close_fd(&fd, 0);
	open_fd(sh, &fd);
	fd = SH_FD_MAX - 1;
	close_fd(&fd, 3);
	sh->pipe->stdincpy = dup(STDIN_FILENO);
	sh->pipe->stdoutcpy = dup(STDOUT_FILENO);
	sh->pipe->stderrcpy = dup(STDERR_FILENO);
	sh->pipe->fd_aliases[STDIN_FILENO] = sh->pipe->stdincpy;
	sh->pipe->fd_aliases[STDOUT_FILENO] = sh->pipe->stdoutcpy;
	sh->pipe->fd_aliases[STDERR_FILENO] = sh->pipe->stderrcpy;
	if (sh->pipe->fd_aliases[STDIN_FILENO] < 0
		|| sh->pipe->fd_aliases[STDOUT_FILENO] < 0
		|| sh->pipe->fd_aliases[STDERR_FILENO] < 0)
		ft_exit_error("open failed\n", -1);
}
