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

static int	is_nb(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

static int	test_file_access(char *file)
{
	if (!access(file, F_OK))
	{
		if (access(file, W_OK) < 0)
		{
			ft_err_print(file, NULL, "Permission denied", 2);
			return (0);
		}
	}
	return (1);
}

static void	redir_to_file(t_aggregate *node, t_shell *sh)
{
	node->cmd = init_redir_wrap(ft_strdup(node->dest), node->cmd, \
		RE_OUT_ONE, node->close_fd);
	exec_tree(node->cmd, &sh->env, sh->terminal, sh);
}

static void	exec_aggre_split(t_aggregate *node, int *open_fd, t_shell *sh)
{
	// ft_printf("OPENFD: %d\n", *open_fd);
	if (fcntl(*open_fd, F_GETFD) >= 0 && sh->pipe->piping)
	{
		if (*open_fd == STDOUT_FILENO)
			if (fcntl(*open_fd, F_GETFD) >= 0 && dup2(sh->pipe->write_pipe[1], node->close_fd) < 0)
				exit_error(sh, 1, "dup2 failed");
	}
	else if (fcntl(*open_fd, F_GETFD) >= 0 && dup2(*open_fd, node->close_fd) < 0)
		exit_error(sh, 1, "dup2 failed");
	else if (fcntl(*open_fd, F_GETFD) < 0 && fcntl(node->close_fd, F_GETFD) >= 0)
	{
		if (node->close_fd == STDOUT_FILENO)
			sh->pipe->close_fd = STDOUT_FILENO;
		close(node->close_fd);
		sh->pipe->close_fd = 1;
	}
	if (node->cmd && node->cmd->type == CMD && node->close_fd == STDOUT_FILENO)
		sh->pipe->redir_out = 1;
	else if (node->cmd && node->cmd->type == CMD \
	&& node->close_fd == STDIN_FILENO)
		sh->pipe->redir_in = 1;
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

void	exec_aggregate(t_aggregate *node, char ***environ_cp, \
char *terminal, t_shell *sh)
{
	struct stat	buf;
	int			open_fd;
	// int			cp_fd;
	int 		skip;

	skip = 0;
	open_fd = -1;
	if (is_nb(node->dest))
		open_fd = ft_atoi(node->dest);
	else if (node->close_fd == 1)
	{
		if (!test_if_file(node->dest) || !test_file_access(node->dest))
			return ;
		redir_to_file(node, sh);
		return ;
	}
	// if (fcntl(open_fd, F_GETFD) < 0 )
	// 	skip = 1;
	// if (fcntl(node->close_fd, F_GETFD) < 0 || fcntl(open_fd, F_GETFD) < 0)
	// 	sh->pipe->close_fd = node->close_fd; //Dont open stdout in child
	if (sh->pipe->closed_fds[open_fd] < 1 && (fstat(open_fd, &buf) < 0 || fcntl(open_fd, F_GETFD) < 0
		|| is_pipe(sh, open_fd) || if_previous_redir(sh, open_fd)))
	{
		ft_err_print(node->dest, NULL, "Bad file descriptor", 2);
		sh->exit_stat = 1;
		return ;
	}
	// cp_fd = dup(node->close_fd);
	// sh->pipe->previous_redir[cp_fd] = 1;
	// if (!skip)
		exec_aggre_split(node, &open_fd, sh);
	exec_tree(node->cmd, environ_cp, terminal, sh);
	// if (cp_fd >= 0)
	// 	dup2(cp_fd, node->close_fd);
}
