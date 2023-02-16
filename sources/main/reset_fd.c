/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:31:23 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/16 18:16:08 by jniemine         ###   ########.fr       */
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
	ft_memset(sh->pipe->fd_aliases, -1, sizeof(int) * SH_FD_MAX);
	sh->pipe->stdincpy = dup(STDIN_FILENO);
	sh->pipe->stdoutcpy = dup(STDOUT_FILENO);
	sh->pipe->stderrcpy = dup(STDERR_FILENO);
	// ft_putstr_fd("STDOUTCPY: ", 2);
	// ft_putnbr_fd(sh->pipe->stdoutcpy, 2);
	// ft_putstr_fd("\n", 2);
	sh->pipe->std_fd_copies[0] = sh->pipe->stdincpy;
	sh->pipe->std_fd_copies[1] = sh->pipe->stdoutcpy;
	sh->pipe->std_fd_copies[2] = sh->pipe->stderrcpy;
	if (sh->pipe->std_fd_copies[STDIN_FILENO] < 0
		|| sh->pipe->std_fd_copies[STDOUT_FILENO] < 0
		|| sh->pipe->std_fd_copies[STDERR_FILENO] < 0)
		ft_exit_error("open failed\n", -1);
}
