/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:31:23 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/13 00:21:14 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	reset_fd(t_shell *sh)
{
	int		fd;
	char	*terminal;

	fd = SH_FD_MAX;
	terminal = sh->terminal;
	while (fd >= 0)
	{
		close(fd);
		--fd;
	}
	fd = 0;
	while (fd <= SH_FD_MAX)
	{
		open(terminal, O_RDWR);
		++fd;
	}
	fd = SH_FD_MAX - 1; //255 seems to be open always with bash?
	while (fd >= 3)
	{
		close(fd);
		--fd;
	}
	sh->pipe->stdincpy = dup(STDIN_FILENO);
	sh->pipe->stdoutcpy = dup(STDOUT_FILENO);
	sh->pipe->fd_aliases[sh->pipe->stdincpy] = open(terminal, O_RDWR);
	sh->pipe->fd_aliases[sh->pipe->stdoutcpy] = open(terminal, O_RDWR);
	if (sh->pipe->fd_aliases[sh->pipe->stdincpy] < 0
		|| sh->pipe->fd_aliases[sh->pipe->stdoutcpy] < 0)
		ft_exit_error("open failed\n", -1);
}

