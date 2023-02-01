/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:14:38 by jakken            #+#    #+#             */
/*   Updated: 2023/02/01 21:51:53 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	test_file_access_for_type(char *dest, int closefd, int *rights)
{
	if (test_if_file(dest))
	{
		if (access(dest, F_OK) < 0)
		{
			if (closefd > STDIN_FILENO)
				return (1);
			else
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

void	exec_redir(t_redir *node, char ***environ_cp,
				char *terminal, t_shell *sh)
{
	int	fd;

	if (!test_file_access_for_type(node->filepath,
			node->close_fd, &node->open_flags))
		return ;
	open_fd_if_needed(node->close_fd, terminal);
	fd = open(node->filepath, node->open_flags, node->rights);
	if (fd < 0)
	{
		ft_err_print(NULL, node->filepath, "open failed", 2);
		return ;
	}
	if (dup2(fd, node->close_fd) < 0)
	{
		ft_err_print(NULL, "exec_redir", "dup2 failed", 2);
		return ;
	}
	if (node->cmd && node->cmd->type == CMD)
		((t_cmdnode *)node->cmd)->redirecting = 1;
	if (sh->pipe->pipefd[0] > 0 || sh->pipe->pipefd[1] > 0)
	{
		close(sh->pipe->pipefd[0]);
		close(sh->pipe->pipefd[1]);
		sh->pipe->pipefd[0] = -1;
		sh->pipe->pipefd[1] = -1;
	}
	exec_tree(node->cmd, environ_cp, terminal, sh);
	reset_fd(sh->terminal);
	close(fd);
}
