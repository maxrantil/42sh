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

static int	test_access_type(char *dest, int closefd, int *rights, t_shell *sh)
{
	struct stat buf;

	stat(dest, &buf);
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
			if (S_ISFIFO(buf.st_mode) && ft_err_print(dest, NULL, \
			"Is a named pipe", 2)) //This is preventing the hangin and memleak after ctrl + c
				return (0);
			if (*rights & O_CREAT & O_TRUNC)
				*rights = O_WRONLY;
			return (1);
		}
		ft_err_print(dest, NULL, "Permission denied", 2);
	}
	return (0);
}

static int open_file(t_redir *node, char *terminal, t_shell *sh, int *fd)
{
	struct stat buf;

	open_fd_if_needed(&node->close_fd, terminal, sh);
	stat(node->filepath, &buf);
	*fd = open(node->filepath, node->open_flags, node->rights);
	if (S_ISFIFO(buf.st_mode))
		return (1);
	if (*fd < 0)
		exit_error(sh, 1, "open failed");
	return (0);
}

void	exec_redir(t_redir *node, char ***environ_cp, \
char *terminal, t_shell *sh)
{
	int	fd;
	int	cpy;

	fd = -1;
	// if (!sh->pipe->redir_fork)
	// {
	// 	sh->pipe->redir_fork = 1;
	// 	fork_wrap();
	// }
	if (!test_access_type(node->filepath,
			node->close_fd, &node->open_flags, sh))
		return ;
	if (open_file(node, terminal, sh, &fd))
		return ;
	sh->pipe->previous_redir[fd] = 1;
	cpy = dup(node->close_fd);
	sh->pipe->previous_redir[cpy] = 1;
	if (sh->pipe->previous_redir[node->close_fd] == 1)
		sh->pipe->previous_redir[node->close_fd] = 0;
	sh->pipe->write_fd = fd;
	sh->pipe->close_fd = node->close_fd;
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
	sh->pipe->close_fd = -1;
	// sh->pipe->write_fd = -1;
	// if (dup2(cpy, node->close_fd) < 0)
	// 	exit_error(sh, 1, "exec_redir dup2 failed");
}
