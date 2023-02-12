/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_open_fd_if_needed.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:13:07 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/13 01:22:15 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	open_until_fd(int fd, char *terminal)
{
	int	i;

	i = -1;
	while (1)
	{
		i = open(terminal, O_RDWR);
		if (i < 0)
		{
			ft_err_print(NULL, "open_fd_if_needed", "open failed", 2);
			break ;
		}
		if (i >= fd)
			break ;
	}
}

static void	close_previously_closed(int fd, int *closefd)
{
	int	i;

	i = 0;
	while (i < fd)
	{
		ft_printf("I: %d\n", i);
		if (i != SH_FD_MAX && closefd[i] == 1 && close(i) < 0)
		{
			ft_err_print(NULL, "open_fd_if_needed", "close failed", 2);
			exit(-1);
		}
		++i;
	}
}

void	open_fd_if_needed(int *fd, char *terminal, t_shell *sh)
{
	struct stat	buf;
	int			*closefd;
	int			i;
	int			len;

	if (alias_fd_if_necessary(sh, fd))
		return ;
	if (*fd <= 0)
		len = 2;
	else
		len = *fd + 1;
	closefd = ft_memalloc(sizeof(*closefd) * len);
	closefd[0] = 0;
	closefd[1] = 0;
	i = 0;
	if (fstat(*fd, &buf) < 0 || fcntl(*fd, F_GETFD) < 0)
	{
		while (i <= *fd)
		{
			if (fstat(i, &buf) < 0 || fcntl(*fd, F_GETFD) < 0)
				closefd[i] = 1;
			++i;
		}
		open_until_fd(*fd, terminal);
		close_previously_closed(*fd, closefd);
	}
	free(closefd);
}
