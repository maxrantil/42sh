/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:15:20 by jakken            #+#    #+#             */
/*   Updated: 2023/02/01 03:30:11 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell *g_sh;

void	error_exit(char *msg)
{
	ft_putstr_fd("ERROR: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(-1);
}

int	fork_wrap(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_exit("fork failed\n");
	if (pid == 0)
		ft_signal_dfl();
	else
		set_signal_exec();
	return (pid);
}

int	pipe_wrap(int pipefd[])
{
	if (pipe(pipefd) < 0)
	{
		ft_err_print(NULL, "pipe failed", "exec_pipe", 2);
		return (1);
	}
	return (0);
}

void	 exec_pipe(t_pipenode *pipenode,
		char ***environ_cp, char *terminal, t_shell *sh)
{
	if (pipe_wrap(sh->pipe->pipefd))
		return ;
	exec_tree(pipenode->left, environ_cp, terminal, sh);
	if (dup2(sh->pipe->pipefd[0], STDIN_FILENO) < 0)
		ft_err_print("dup2", "PARENT", "failed", 2);
	close (sh->pipe->pipefd[1]);
	sh->pipe->pipefd[1] = -1;
	exec_tree(pipenode->right, environ_cp, terminal, sh);
}
