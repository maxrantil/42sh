/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:14:38 by jakken            #+#    #+#             */
/*   Updated: 2023/02/17 05:0 by jniemine         ###   ########.fr       */
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

static int	test_file_access_for_type(char *dest, int closefd, int *rights, t_shell *sh)
{
	if (protect_fd(closefd, sh))
		return (0);
	if (test_if_file(dest))
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
		ft_err_print(dest, NULL, "Permission denied", 2);
	}
	return (0);
}

static void	open_file(t_redir *node, char *terminal, t_shell *sh, int *fd)
{
	int	fd_temp;

	open_fd_if_needed(&node->close_fd, terminal, sh);
	*fd= open(node->filepath, node->open_flags, node->rights);
	// if (sh->pipe->open_fd_idx >= 0)
	// 	*fd = fcntl(fd_temp, F_DUPFD, sh->pipe->open_fd_idx--);
	// else
	// 	error_exit("Too many open files");
	// close(fd_temp);
	// sh->pipe->fd_aliases[node->close_fd] = *fd;
	// if (node->open_flags == O_RDONLY)
	// 	sh->pipe->read_fd = *fd;
	if (*fd < 0)
		exit_error(sh, 1, "open failed");
}

void	exec_redir(t_redir *node, char ***environ_cp, \
char *terminal, t_shell *sh)
{
	int	fd;
	int cpy;

	fd = -1;

	if (!test_file_access_for_type(node->filepath,
			node->close_fd, &node->open_flags, sh))
		return ;
	open_file(node, terminal, sh, &fd);
	sh->pipe->previous_redir[fd] = 1;
	cpy = dup(node->close_fd);
	sh->pipe->previous_redir[cpy] = 1;
	if (sh->pipe->previous_redir[node->close_fd] == 1)
		sh->pipe->previous_redir[node->close_fd] = 0;
	if (dup2(fd, node->close_fd) < 0)
		exit_error(sh, 1, "exec_redir dup2 failed");
	if (node->close_fd == STDOUT_FILENO)
		sh->pipe->redir_out = 1;
	else if (node->close_fd == STDIN_FILENO)
		sh->pipe->redir_in = 1;
	if (sh->pipe->write_pipe[1] > 0 && node->close_fd == STDOUT_FILENO)
	{
		close(sh->pipe->write_pipe[1]);
		sh->pipe->write_pipe[1] = -1;
	}
	exec_tree(node->cmd, environ_cp, terminal, sh);
	// close(sh->pipe->previous_redir[node->close_fd]);
	dup2(cpy, node->close_fd); // PROTECT
	// reset_fd(sh);
}
