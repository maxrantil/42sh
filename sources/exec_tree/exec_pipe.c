/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:15:20 by jakken            #+#    #+#             */
/*   Updated: 2023/01/30 18:30:18 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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

void	exec_pipe(t_pipenode *pipenode,
		char ***environ_cp, char *terminal, t_shell *sh)
{
	int	pipefd[2];
	int local;

	if (pipe_wrap(pipefd))
		return ;
	if ((local = fork_wrap()) == 0)
	{
		ft_signal_dfl();
		signal(SIGCHLD, SIG_IGN);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_tree(pipenode->left, environ_cp, terminal, sh);
		ft_putstr_fd("AFTER FIRST PIPE\n ", STDERR_FILENO);
		exit (1);
	}
	ft_putstr_fd("local: ", STDERR_FILENO);
	ft_putnbr_fd(local, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if ((local = fork_wrap()) == 0)
	{
		ft_signal_dfl();
		signal(SIGCHLD, SIG_IGN);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_tree(pipenode->right, environ_cp, terminal, sh);
		ft_putstr_fd("AFTER SECOND PIPE\n ", STDERR_FILENO);
		exit (1);
	}
	ft_putstr_fd("local_two: ", STDERR_FILENO);
	ft_putnbr_fd(local, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(0);
	wait(0);
}
