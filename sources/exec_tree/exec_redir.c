/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:53:25 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/25 15:44:34 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

static int	open_file(t_redir *node, char *terminal, t_shell *sh, int *fd)
{
	struct stat	buf;

	terminal = NULL;
	stat(node->filepath, &buf);
	if (S_ISFIFO(buf.st_mode))
	{
		node->open_flags = O_WRONLY;
		sh->pipe->interrupt = 1;
	}
	*fd = open(node->filepath, node->open_flags, node->rights);
	if (sh->pipe->interrupt)
	{
		ft_err_print(NULL, "fifo", "Interrupted system call", 2);
		return (1);
	}
	if (*fd < 0)
		exit_error(sh, 1, "open failed");
	return (0);
}

static int	fork_if_needed(t_redir *node, t_shell *sh)
{
	int			builtin;
	char		**cmd;
	struct stat	buf;

	builtin = 0;
	cmd = get_cmd_name((t_treenode *)node);
	builtin = is_builtin(cmd);
	if (!stat(node->filepath, &buf) && S_ISFIFO(buf.st_mode))
		builtin = 0;
	if (!sh->pipe->redir_fork && !builtin)
	{
		sh->pipe->pid = fork_wrap();
		sh->pipe->redir_fork = 1;
		if (sh->pipe->pid != 0)
		{
			update_fg_job(sh, sh->pipe->pid, cmd);
			sh->pipe->redir_fork = 0;
		}
	}
	return (builtin);
}

static void	exec_redir_split(t_redir *node, int fd, t_shell *sh)
{
	if (dup2(fd, node->close_fd) < 0)
		exit_error(sh, 1, "exec_redir dup2 failed");
	if (sh->pipe->write_pipe[1] > 0 && node->close_fd == STDOUT_FILENO)
	{
		close(sh->pipe->write_pipe[1]);
		sh->pipe->write_pipe[1] = -1;
	}
}

static int	test_access_wrap(t_redir *node, t_shell *sh)
{
	if (!test_access_type(node->filepath, \
	node->close_fd, &node->open_flags, sh))
	{
		if (sh->pipe->redir_fork)
			exit (1);
		sh->exit_stat = 1;
		return (1);
	}
	return (0);
}

void	exec_redir(t_redir *node, char ***environ_cp, \
char *terminal, t_shell *sh)
{
	int		fd;
	int		cpy;
	int		builtin;

	if (test_access_wrap(node, sh))
		return ;
	builtin = fork_if_needed(node, sh);
	if (sh->pipe->pid == 0 || builtin)
	{
		if (open_file(node, terminal, sh, &fd))
		{
			if (!builtin)
				exit (1);
			return ;
		}
		sh->pipe->previous_redir[fd] = 1;
		cpy = dup(node->close_fd);
		sh->pipe->previous_redir[cpy] = 1;
		if (sh->pipe->previous_redir[node->close_fd] == 1)
			sh->pipe->previous_redir[node->close_fd] = 0;
		sh->pipe->close_fd = node->close_fd;
		exec_redir_split(node, fd, sh);
		exec_tree(node->cmd, environ_cp, terminal, sh);
		sh->pipe->redir_fork = 0;
	}
}
