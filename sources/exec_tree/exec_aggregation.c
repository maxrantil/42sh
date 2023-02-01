/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aggregation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:26:00 by jakken            #+#    #+#             */
/*   Updated: 2023/02/01 22:00:35 by jniemine         ###   ########.fr       */
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
	node->cmd = init_redir_wrap(ft_strdup(node->dest), node->cmd,
			RE_OUT_ONE, node->close_fd);
	exec_tree(node->cmd, &sh->env, sh->terminal, sh);
}

void	exec_aggregate(t_aggregate *node, char ***environ_cp,
		char *terminal, t_shell *sh)
{
	struct stat	buf;
	int			open_fd;

	open_fd_if_needed(node->close_fd, terminal);
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
	if (fstat(open_fd, &buf) < 0)
	{
		ft_err_print(node->dest, NULL, "Bad file descriptor", 2);
		return ;
	}
	if (dup2(open_fd, node->close_fd) < 0)
	{
		ft_err_print(NULL, "dup2", "failed", 2);
		return ;
	}
	if (node->cmd && node->cmd->type == CMD)
		((t_cmdnode *)node->cmd)->redirecting = 1;
	exec_tree(node->cmd, environ_cp, terminal, sh);
	reset_fd(sh->terminal);
	close (open_fd);
}
