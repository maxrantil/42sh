/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_alias_for_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:02:12 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/17 08:58:51 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	give_alias_for_fd(t_shell *sh, int *fd)
{
	int	alias_fd;
	int	temp_fd;

	if (*fd >= SH_FD_MAX)
		ft_exit_error("Too many open filedescriptors\n", -1);
	if (fcntl(*fd, F_GETFD) == -1)
	{
		alias_fd = open(sh->terminal, O_RDWR);
		if (alias_fd < 0)
			ft_exit_error("open failed\n", alias_fd);
		temp_fd = fcntl(alias_fd, F_DUPFD, sh->pipe->open_fd_idx--);
		if (temp_fd < 0)
			ft_exit_error("fcntl failed\n", temp_fd);
		close(alias_fd);
		alias_fd = temp_fd;
	}
	else
		alias_fd = dup(*fd);
	if (alias_fd < 0)
		ft_exit_error("open failed\n", alias_fd);
	sh->pipe->fd_aliases[*fd] = alias_fd;
	*fd = alias_fd;
	return (1);
}

int	alias_fd_if_necessary(t_shell *sh, int *fd)
{
	int	i;

	i = 0;
	if (*fd < 3 || *fd >= SH_FD_MAX)
		return (0);
	if (is_aliased_fd(sh, *fd))
	{
		*fd = sh->pipe->fd_aliases[*fd];
		return (1);
	}
	while (i < SH_FD_MAX)
	{
		if (sh->pipe->fd_aliases[i] == *fd)
			return (give_alias_for_fd(sh, fd));
		++i;
	}
	return (0);
}

int	close_fd_alias_if_necessary(t_shell *sh, int fd)
{
	if (fd > 1 && fd <= SH_FD_MAX && sh->pipe->fd_aliases[fd] != -1)
	{
		close(sh->pipe->fd_aliases[fd]);
		sh->pipe->fd_aliases[fd] = -1;
		return (1);
	}
	return (0);
}

int	is_aliased_fd(t_shell *sh, int open_fd)
{
	if (open_fd <= SH_FD_MAX && sh->pipe->fd_aliases[open_fd] != -1)
		return (1);
	return (0);
}

int	is_std_fd_cpy(t_shell *sh, int fd)
{
	if (sh->pipe->stdincpy == fd || sh->pipe->stdoutcpy == fd
		|| sh->pipe->stderrcpy == fd)
		return (1);
	return (0);
}
