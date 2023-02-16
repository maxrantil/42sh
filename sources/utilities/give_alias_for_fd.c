/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_alias_for_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:02:12 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/16 12:53:45 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	give_alias_for_fd(t_shell *sh, int *fd)
{
	int alias_fd;

	if (*fd >= SH_FD_MAX)
		ft_exit_error("Too many open filedescriptors\n", -1);
	// alias_fd = open(sh->terminal, O_RDWR);
	alias_fd = dup(*fd); // PROTECT
	if (alias_fd < 0)
		ft_exit_error("open failed\n", alias_fd);
	sh->pipe->fd_aliases[*fd] = alias_fd;
	*fd = alias_fd;
	return (1);
}

int	alias_fd_if_necessary(t_shell *sh, int *fd)
{
	int i;

	i = 0;
	if (*fd < 3 || *fd >= SH_FD_MAX)
		return 0;
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

int close_fd_alias_if_necessary(t_shell *sh, int fd)
{
	if (fd > 1 && fd <= SH_FD_MAX && sh->pipe->fd_aliases[fd] != -1)
	{
		close(sh->pipe->fd_aliases[fd]);
		sh->pipe->fd_aliases[fd] = -1;
		return (1);
	}
	return (0);
}

//echo lol > 1 1>2 1>&6304
int is_aliased_fd(t_shell *sh, int open_fd)
{
	if (open_fd > STDERR_FILENO && open_fd <= SH_FD_MAX && sh->pipe->fd_aliases[open_fd] != -1)
		return (1);
	return (0);
}

int is_alias_fd(t_shell *sh, int fd)
{
	int i;

	i = 0;
	while (i < SH_FD_MAX)
	{
		if (sh->pipe->fd_aliases[i] == fd)
			return (1);
		++i;
	}
	return (0);
}

void print_aliases(t_shell *sh)
{
	int i;

	i = 0;
	while (i < SH_FD_MAX)
	{
		if (sh->pipe->fd_aliases[i] != -1)
		{
			ft_printf("ALIAS: %d -> %d\n", i, sh->pipe->fd_aliases[i]);
			ft_putstr_fd("ALIAS: ", 2);
			ft_putnbr_fd(i, 2);
			ft_putstr_fd(" -> ", 2);
			ft_putnbr_fd(sh->pipe->fd_aliases[i], 2);
			ft_putchar_fd('\n', 2);
		}
		++i;
	}
}

//Maybe do recursive closing if the alias has an alias?
int close_fd_alias(t_shell *sh, int fd)
{
	if (fd > STDOUT_FILENO && fd <= SH_FD_MAX)
		sh->pipe->fd_aliases[fd] = -1;
	return (1);
}
