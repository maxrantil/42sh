/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:14:38 by jakken            #+#    #+#             */
/*   Updated: 2023/02/16 16:48:17 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	test_file_access_for_type(char *dest, int closefd, int *rights)
{
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

void	exec_redir(t_redir *node, char ***environ_cp, \
char *terminal, t_shell *sh)
{
	int	fd;

	//TODO HERE WE OPEN 3 SO IT SHOULD BE OPEN ls > 1 > 2 > 3 3>4 > 5 1>&3
	if (!test_file_access_for_type(node->filepath,
			node->close_fd, &node->open_flags))
		return ;
	// ft_putstr_fd("CLOSEFD: ", 2);
	// ft_putnbr_fd(node->close_fd, 2);
	// ft_putstr_fd("\n", 2);
	// open_fd_if_needed(&node->close_fd, terminal, sh);
	// ft_putstr_fd("CLOSEFD: ", 2);
	// ft_putnbr_fd(node->close_fd, 2);
	// ft_putstr_fd("\n", 2);
	fd = open(node->filepath, node->open_flags, node->rights);
	if (fd < 0)
		exit_error(sh, 1, "open failed");
	give_alias_for_fd(sh, &fd);
	// print_aliases(sh);
	// ft_putstr_fd("--------------------------------------------\n", 2);
	// alias_fd_if_necessary(sh, &fd);
	// print_aliases(sh);
	// ft_putstr_fd("--------------------------------------------\n", 2);
	// ft_putstr_fd("CLOSEFD: ", 2);
	// ft_putnbr_fd(node->close_fd, 2);
	// ft_putstr_fd(" FD: ", 2);
	// ft_putnbr_fd(fd, 2);
	// ft_putstr_fd("\n", 2);
	if (close_fd_alias(sh, node->close_fd) && dup2(fd, node->close_fd) < 0)
		exit_error(sh, 1, "exec_redir dup2 failed");
	if (node->cmd && node->cmd->type == CMD && node->close_fd == STDOUT_FILENO)
		sh->pipe->redir_out = 1;
	else if (node->cmd && node->cmd->type == CMD \
	&& node->close_fd == STDIN_FILENO)
		sh->pipe->redir_in = 1;
	if (sh->pipe->write_pipe[1] > 0 && node->close_fd == STDOUT_FILENO)
	{
		close(sh->pipe->write_pipe[1]);
		sh->pipe->write_pipe[1] = -1;
	}
	exec_tree(node->cmd, environ_cp, terminal, sh);
}
