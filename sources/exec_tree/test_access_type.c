/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_access_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:39:08 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/25 03:08:37 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	protect_fd(int closefd, t_shell *sh)
{
	if (closefd > 255 || closefd < 0)
	{
		ft_err_print(ft_itoa(closefd), NULL, "Bad file descriptor", 2);
		sh->exit_stat = 1;
		return (1);
	}
	return (0);
}

static int	test_access_split(char *dest, int closefd, int *rights)
{
	if (access(dest, F_OK) < 0)
	{
		if (*rights & O_CREAT)
			return (1);
		if (!(*rights & O_CREAT))
		{
			ft_err_print(dest, NULL, "No such file or directory", 2);
			return (0);
		}
	}
	if (closefd == STDIN_FILENO && !access(dest, R_OK))
		return (1);
	else if (closefd >= STDOUT_FILENO && !access(dest, W_OK))
	{
		if (*rights & O_CREAT & O_TRUNC)
			*rights = O_WRONLY;
		return (1);
	}
	return (2);
}

int	test_access_type(char *dest, int closefd, int *rights, t_shell *sh)
{
	struct stat	buf;
	int			ret;

	stat(dest, &buf);
	if (protect_fd(closefd, sh))
		return (0);
	if (test_if_file(dest))
	{
		ret = test_access_split(dest, closefd, rights);
		if (ret < 2)
			return (ret);
		ft_err_print(dest, NULL, "Permission denied", 2);
	}
	return (0);
}
