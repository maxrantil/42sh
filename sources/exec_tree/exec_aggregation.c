/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aggregation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:26:00 by jakken            #+#    #+#             */
/*   Updated: 2023/02/23 17:10: by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	exec_aggre_split(t_aggregate *node, int *open_fd, t_shell *sh)
{
	if (fcntl(*open_fd, F_GETFD) >= 0 && sh->pipe->piping)
	{
		if (*open_fd == STDOUT_FILENO)
			if (fcntl(*open_fd, F_GETFD) >= 0 && dup2(sh->pipe->write_pipe[1] \
			, node->close_fd) < 0)
				exit_error(sh, 1, "dup2 failed");
	}
	else if (fcntl(*open_fd, F_GETFD) >= 0 \
	&& dup2(*open_fd, node->close_fd) < 0)
		exit_error(sh, 1, "dup2 failed");
	else if (fcntl(*open_fd, F_GETFD) < 0 && \
	fcntl(node->close_fd, F_GETFD) >= 0)
	{
		close(node->close_fd);
		sh->pipe->close_fd = 1;
	}
	sh->pipe->close_fd = 1;
}

static int	if_previous_redir(t_shell *sh, int dest)
{
	int	i;

	i = 0;
	while (i < SH_FD_MAX)
	{
		if (sh->pipe->previous_redir[dest] == 1)
			return (1);
		++i;
	}
	return (0);
}

static int	fork_if_needed(t_aggregate *node, t_shell *sh)
{
	int			builtin;
	char		**cmd;
	struct stat	buf;

	builtin = 0;
	cmd = get_cmd_name((t_treenode *)node);
	if (cmd)
		builtin = is_builtin(cmd);
	if (!is_nb(node->dest) && !stat(node->dest, &buf) && S_ISFIFO(buf.st_mode))
		builtin = 0;
	if (!sh->pipe->redir_fork && !builtin)
	{
		sh->pipe->pid = fork_wrap();
		sh->pipe->redir_fork = 1;
		if (sh->pipe->pid != 0)
		{
			update_fg_job(sh, sh->pipe->pid, cmd);
			sh->pipe->redir_fork = 0;
			wait_for_job(sh, sh->pipe->pid);
		}
	}
	return (builtin);
}

static void	write_to_file(t_aggregate *node, t_shell *sh)
{
	if (!test_if_file(node->dest) || !test_file_access(node->dest))
		return ;
	redir_to_file(node, sh);
	return ;
}

void	exec_aggregate(t_aggregate *node, char ***environ_cp, \
char *terminal, t_shell *sh)
{
	struct stat	buf;
	int			open_fd;
	int			builtin;

	builtin = fork_if_needed(node, sh);
	if (sh->pipe->pid == 0 || builtin)
	{
		open_fd = -1;
		if (is_nb(node->dest))
			open_fd = ft_atoi(node->dest);
		else if (node->close_fd == 1)
			write_to_file(node, sh);
		if (sh->pipe->closed_fds[open_fd] < 1 \
			&& (fstat(open_fd, &buf) < 0 || fcntl(open_fd, F_GETFD) < 0 \
				|| is_pipe(sh, open_fd) || if_previous_redir(sh, open_fd)))
		{
			ft_err_print(node->dest, NULL, "Bad file descriptor", 2);
			sh->exit_stat = 1;
			if (!builtin)
				exit (1);
			return ;
		}
		exec_aggre_split(node, &open_fd, sh);
		exec_tree(node->cmd, environ_cp, terminal, sh);
		if (!builtin)
			exit (1);
	}
}
