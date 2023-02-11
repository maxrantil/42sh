/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:15:20 by jakken            #+#    #+#             */
/*   Updated: 2023/02/09 15:29:58y jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

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
	return (pid);
}

int	pipe_wrap(int write_pipe[])
{
	if (pipe(write_pipe) < 0)
	{
		ft_err_print(NULL, "pipe failed", "exec_pipe", 2);
		return (1);
	}
	return (0);
}

void	exec_pipe(t_pipenode *pipenode, \
		char ***environ_cp, char *terminal, t_shell *sh)
{
	if (pipe_wrap(sh->pipe->write_pipe))
		return ;
	sh->pipe->read_pipe[1] = dup(sh->pipe->write_pipe[1]);
	exec_tree(pipenode->left, environ_cp, terminal, sh);
	sh->pipe->read_pipe[0] = dup(sh->pipe->write_pipe[0]);
	if (dup2(sh->pipe->read_pipe[0], STDIN_FILENO) < 0)
	{
		ft_err_print("dup", NULL, "failed in exec_pipe", 2);
		exit (1);
	}
	g_sh->pipe->redir_out = 0;
	close (sh->pipe->write_pipe[1]);
	sh->pipe->write_pipe[1] = -1;
	close(sh->pipe->read_pipe[1]);
	sh->pipe->read_pipe[1] = -1;
	exec_tree(pipenode->right, environ_cp, terminal, sh);
	if (sh->ampersand)
	{
		waitpid(-1, 0, WNOHANG | WUNTRACED);
		waitpid(-1, 0, WNOHANG | WUNTRACED);
	}
	else
	{
		waitpid(-1, 0, WUNTRACED);
		waitpid(-1, 0, WUNTRACED);
	}
	reset_fd(terminal);
	sh->pipe->stdincpy = dup(STDIN_FILENO);
	sh->pipe->stdoutcpy = dup(STDOUT_FILENO);
	close(sh->pipe->write_pipe[0]);
	close(sh->pipe->write_pipe[1]);
	sh->pipe->write_pipe[1] = -1;
	sh->pipe->write_pipe[0] = -1;
}
