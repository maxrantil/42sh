/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_open_fd_if_needed.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:13:07 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/25 04:12:05 by jniemine         ###   ########.fr       */
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
		if (i != SH_FD_MAX && closefd[i] == 1)
			close(i);
		++i;
	}
}

static int	init_open_fd(int *fd, t_shell *sh, int **closefd)
{
	int	len;

	if (!sh)
		return (1);
	if (*fd <= 0)
		len = 2;
	else
		len = *fd + 1;
	*closefd = ft_memalloc(sizeof(**closefd) * len);
	ft_bzero(*closefd, sizeof(**closefd) * len);
	return (0);
}

void	open_fd_if_needed(int *fd, char *terminal, t_shell *sh)
{
	int			i;
	struct stat	buf;
	int			*closefd;

	if (init_open_fd(fd, sh, &closefd))
		return ;
	i = 0;
	if (fstat(*fd, &buf) < 0 || fcntl(*fd, F_GETFD) < 0)
	{
		while (i <= *fd)
		{
					ft_putstr_fd("CLOSEFD: ", 2);
			ft_putnbr_fd(i, 2);
			ft_putstr_fd(" ", 2);
			ft_putnbr_fd(closefd[i], 2);
			ft_putstr_fd("\n", 2);
			if (fcntl(i, F_GETFD) < 0 && fstat(i, &buf) < 0)
				closefd[i] = 1;
			ft_putstr_fd("CLOSEFD: ", 2);
			ft_putnbr_fd(i, 2);
			ft_putstr_fd(" ", 2);
			ft_putnbr_fd(closefd[i], 2);
			ft_putstr_fd("\n", 2);
			++i;
		}
		open_until_fd(*fd, terminal);
		close_previously_closed(*fd, closefd);
	}
	free(closefd);
}
