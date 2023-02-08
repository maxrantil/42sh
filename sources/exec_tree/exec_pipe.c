/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:15:20 by jakken            #+#    #+#             */
/*   Updated: 2023/02/06 11:15:40 by mbarutel         ###   ########.fr       */
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

int	pipe_wrap(int pipefd[])
{
	if (pipe(pipefd) < 0)
	{
		ft_err_print(NULL, "pipe failed", "exec_pipe", 2);
		return (1);
	}
	return (0);
}

void	exec_pipe(t_pipenode *pipenode, \
		char ***environ_cp, char *terminal, t_shell *sh)
{
	int status;
	
	if (pipe_wrap(sh->pipe->pipefd))
		return ;
	exec_tree(pipenode->left, environ_cp, terminal, sh);
	//We always dup stdin to pipefd[0] because we always want to read from pipe
	//All the redirectins close fd[1] so there is always EOF in the pipe.
	//For cases like "ls >file | cat", cat reads the EOF from pipe and exits.
	if (dup2(sh->pipe->pipefd[0], STDIN_FILENO) < 0)
	{
		ft_err_print("dup", NULL, "failed", 2);
		exit (1);
	}
	g_sh->pipe->redirecting = 0;
	//In case of normal pipe we want to close fd[1] so that input written into pipe in child process gets EOF
	close (sh->pipe->pipefd[1]);
	sh->pipe->pipefd[1] = -1;
	exec_tree(pipenode->right, environ_cp, terminal, sh);
	// print_fg_node(sh);
	if (sh->ampersand)
		waitpid(sh->fg_node->gpid, &status, WNOHANG | WUNTRACED);
	else
		waitpid(sh->fg_node->gpid, &status, WUNTRACED);
	g_sh->pipe->redirecting = 0;
	reset_fd(terminal);
	close(sh->pipe->pipefd[0]);
	close(sh->pipe->pipefd[1]);
	sh->pipe->pipefd[0] = -1;
}
