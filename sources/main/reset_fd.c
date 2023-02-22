/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:31:23 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/22 10:26:01 by jniemine         ###   ########.fr       */
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
	ft_memset(sh->pipe->pipes, -1, sizeof(int) * SH_FD_MAX * 2);
	sh->pipe->pipe_idx = 0;
	ft_memset(sh->pipe->fd_aliases, -1, sizeof(int) * SH_FD_MAX);
	ft_memset(sh->pipe->previous_redir, -1, sizeof(int) * SH_FD_MAX);
	sh->pipe->open_fd_idx = 254;
	sh->pipe->stdincpy = 255;//fcntl(STDIN_FILENO, F_DUPFD, 255);
	// ft_printf("stdincpy: %d\n", sh->pipe->stdincpy);
	// sh->pipe->stdincpy = fcntl(STDIN_FILENO, F_DUPFD, 252);
	// sh->pipe->stdoutcpy = fcntl(STDOUT_FILENO, F_DUPFD, 253);
	// sh->pipe->stderrcpy = fcntl(STDERR_FILENO, F_DUPFD, 254);
	sh->pipe->read_fd = -1;
	// sh->pipe->std_fd_copies[0] = sh->pipe->stdincpy;
	// sh->pipe->std_fd_copies[1] = sh->pipe->stdoutcpy;
	// sh->pipe->std_fd_copies[2] = sh->pipe->stderrcpy;
	if (sh->pipe->stdincpy < 0/*sh->pipe->std_fd_copies[STDIN_FILENO] < 0
		|| sh->pipe->std_fd_copies[STDOUT_FILENO] < 0
		|| sh->pipe->std_fd_copies[STDERR_FILENO] < 0*/)
		ft_exit_error("open failed\n", -1);
}
