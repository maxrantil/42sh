/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:15:20 by jakken            #+#    #+#             */
/*   Updated: 2023/02/20 16:38:55 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	error_exit(char *msg)
{
	ft_putstr_fd("ERROR: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(-1);
}

static int	pipe_wrap(t_shell *sh, int write_pipe[])
{
	// int *pipe_temp = ft_memalloc(sizeof(int) * 2);
	// if (sh->pipe->pipe_count >= SH_PIPE_MAX)
	// 	{
	// 		ft_err_print(NULL, "Too many pipes", "exec_pipe", 2);
	// 		return (1);
	// 	}; //ERROR RETUNR WITHOUT EXITING
	// if (pipe(pipe_temp) < 0)
	// 	error_exit("pipe failed"); // ERROR EXIT HERE
	// sh->pipe->write_pipe[0] = pipe_temp[0];//sh->pipe->pipes[sh->pipe->pipe_count][0];
	// sh->pipe->write_pipe[1] = pipe_temp[1];//sh->pipe->pipes[sh->pipe->pipe_count][1];
	// ft_printf("write_pipe[0] = %d, write_pipe[1] = %d\n", \
	// 	sh->pipe->write_pipe[0], sh->pipe->write_pipe[1]);
	// int		alias_fd;
	
	if (pipe(write_pipe) < 0)
	{
		ft_err_print(NULL, "pipe failed", "exec_pipe", 2);
		return (1);
	}
	// give_alias_for_fd(sh, &write_pipe[1]);
	// give_alias_for_fd(sh, &write_pipe[0]);
	// alias_fd = fcntl(write_pipe[1], F_DUPFD, sh->pipe->open_fd_idx--);
	// close(write_pipe[1]);
	// write_pipe[1] = alias_fd;
	// // sh->pipe->fd_aliases[write_pipe[1]] = alias_fd;
	// alias_fd = fcntl(write_pipe[0], F_DUPFD, sh->pipe->open_fd_idx--);
	// // sh->pipe->fd_aliases[write_pipe[0]] = alias_fd;
	// close(write_pipe[0]);
	// write_pipe[0] = alias_fd;
	return (0);
}

void	exec_pipe(t_pipenode *pipenode, \
		char ***environ_cp, char *terminal, t_shell *sh)
{
	int		pipe_count;

	if (pipe_wrap(sh, sh->pipe->write_pipe))
		return ;
	pipe_count = sh->pipe->pipe_count;
	// sh->pipe->pipe_count++;
	// sh->pipe->read_pipe[1] = fcntl(sh->pipe->write_pipe[1], 
	// 	F_DUPFD, sh->pipe->open_fd_idx--);
	exec_tree(pipenode->left, environ_cp, terminal, sh);
	// sh->pipe->read_pipe[0] = fcntl(sh->pipe->write_pipe[0], 
	// 	F_DUPFD, sh->pipe->open_fd_idx--);
	if (fcntl(STDIN_FILENO, F_GETFD) < 0)
		dup2(sh->pipe->stdincpy, STDIN_FILENO);// PROTECT
	ft_printf("WRITEPIEP[0] = %d, WRITEPIPE[1] = %d\n", \
		sh->pipe->write_pipe[0], sh->pipe->write_pipe[1]);
	ft_printf("PIPECOUNT: %d\n", pipe_count);
	if (dup2(sh->pipe->write_pipe[0], STDIN_FILENO) < 0)
	{
		ft_err_print("dup", NULL, "failed in exec_pipe", 2);
		exit (1);
	}
	sh->pipe->redir_out = 0;
	close (sh->pipe->write_pipe[1]);
	sh->pipe->write_pipe[1] = -1;
	close (sh->pipe->pipes[sh->pipe->pipe_count][1]);
	close(sh->pipe->read_pipe[1]);
	sh->pipe->read_pipe[1] = -1;
	exec_tree(pipenode->right, environ_cp, terminal, sh);
}
