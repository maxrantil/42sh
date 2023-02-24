/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:14:38 by jakken            #+#    #+#             */
/*   Updated: 2023/02/17 05:0 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	protect_fd(int closefd, t_shell *sh)
{
	if (closefd > 255 || closefd < 0)
	{
		ft_err_print(ft_itoa(closefd), NULL, "Bad file descriptor", 2);
		sh->exit_stat = 1;
		return (1);
	}
	return (0);
}

static int	test_access_type(char *dest, int closefd, int *rights, t_shell *sh)
{
	struct stat buf;

	stat(dest, &buf);
	if (protect_fd(closefd, sh))
		return (0);
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
			// if (S_ISFIFO(buf.st_mode) && ft_err_print(dest, NULL, \
			// "Is a named pipe", 2)) //This is preventing the hangin and memleak after ctrl + c
			// 	return (0);
			if (*rights & O_CREAT & O_TRUNC)
				*rights = O_WRONLY;
			return (1);
		}
		ft_err_print(dest, NULL, "Permission denied", 2);
	}
	return (0);
}
// #include <errno.h>
// #include <stdio.h>
extern t_shell *g_sh;

static void tiny_signal_handler(int num)
{
	if (num == SIGINT)
	{
		ft_err_print(NULL, "fifo", "Interrupted system call", 2);
		g_sh->pipe->interrupt = 1;
	}
}

static int open_file(t_redir *node, char *terminal, t_shell *sh, int *fd)
{
	struct stat buf;
	sig_t			sig;
	struct sigaction sa;

	// sa.sa_handler = tiny_signal_handler;
	sa.sa_flags = 0;
	sig = 0;
	sigemptyset(&sa.sa_mask);
	open_fd_if_needed(&node->close_fd, terminal, sh);
	stat(node->filepath, &buf);
	if (S_ISFIFO(buf.st_mode))
	{
		ft_signal_dfl();
		sig = signal(SIGINT, tiny_signal_handler);
		ft_printf("SIG: %d SIGINT: %d\n", sig, SIGINT);
		// ft_printf("PIDPID: %d\n", sh->pipe->pid);
		node->open_flags = O_WRONLY;
		// node->rights = 0666;
		//signal(SIGINT, SIG_DFL);
	}
	// ft_printf("FILEPATH: %s\n", node->filepath);
	*fd = open(node->filepath, node->open_flags, node->rights);
	ft_printf("SIG: %d SIGINT: %d FD:%d \n", sig, SIGINT, *fd);
	if (sh->pipe->interrupt)
	{
		// ft_init_signals();
		ft_signal_dfl();
		// kill(0, SIGKILL);
		return (1);
	}
	// perror(strerror(errno));
	// ft_putendl_fd("RETURN\n", 2);
	if (*fd < 0)
		exit_error(sh, 1, "open failed");
	return (0);
}

/*
void	exec_child_cmd(t_cmdnode *head, char ***environ_cp, t_shell *sh)
{
	t_cmd	*node;
	char	*path;
	char	*terminal;

	terminal = sh->terminal;
	node = (t_cmd *)head;
	if (node->cmd[0] == NULL)
		return ;
	if (node->cmd[0][0] == '/')
		path = node->cmd[0];
	else
		path = get_path(node->cmd[0], environ_cp, sh);
	if (path == NULL)
	{
		ft_err_print(node->cmd[0], NULL, "command not found", 2);
		exit(127);
	}
	if (execve(path, node->cmd, *environ_cp) < 0)
		exit_error(sh, 1, "execve failed");
}
*/

/*
void	exec_redir_child(t_cmdnode *head, char ***environ_cp, t_shell *sh)
{
	t_redir	*node;
	char	*terminal;
	int		fd;

	terminal = sh->terminal;
	node = (t_redir *)head;
	if (!test_access_type(node->filepath,
			node->close_fd, &node->open_flags, sh))
		return ;
	if (open_file(node, terminal, sh, &fd))
		return ;
	// sh->pipe->previous_redir[fd] = 1;
	// cpy = dup(node->close_fd);
	// sh->pipe->previous_redir[cpy] = 1;
	// if (sh->pipe->previous_redir[node->close_fd] == 1)
	// 	sh->pipe->previous_redir[node->close_fd] = 0;
	sh->pipe->write_fd = fd;
	sh->pipe->close_fd = node->close_fd;
	if (dup2(fd, node->close_fd) < 0)
		exit_error(sh, 1, "exec_redir dup2 failed");
	if (node->close_fd == STDOUT_FILENO)
		sh->pipe->redir_out = 1;
	else if (node->close_fd == STDIN_FILENO)
		sh->pipe->redir_in = 1;
	if (sh->pipe->write_pipe[1] > 0 && node->close_fd == STDOUT_FILENO)
	{
		close(sh->pipe->write_pipe[1]);
		sh->pipe->write_pipe[1] = -1;
	}
	if (node->type != CMD)
		exec_tree(node->cmd, environ_cp, terminal, sh);
	else
		exec_child_cmd(node->cmd, environ_cp, sh);
}
*/

char **get_cmd_name(t_treenode *node)
{
	t_treenode *head;

	head = (t_treenode *)node;

	while (head->type != CMD)
	{
		if ((head)->type == REDIR)
			head = (((t_redir *)(head))->cmd);
		else if ((head)->type == AGGREGATION)
			head = (((t_aggregate *)(head))->cmd);
		else if ((head)->type == CLOSEFD)
			head = (((t_closefd *)(head))->cmd);
	}
	return (((t_cmdnode *)head)->cmd);
}

void	exec_redir(t_redir *node, char ***environ_cp, \
char *terminal, t_shell *sh)
{
	int		fd;
	int		cpy;
	char	**cmd;
	int		builtin;
	struct stat buf;

	terminal = NULL;
	fd = -1;
	builtin = 0;
	cmd = get_cmd_name((t_treenode *)node);
	if (!test_access_type(node->filepath, \
		node->close_fd, &node->open_flags, sh))
			return ;
	builtin = is_builtin(cmd);
	if (!stat(node->filepath, &buf) && S_ISFIFO(buf.st_mode))
		builtin = 0;
	if (!sh->pipe->redir_fork && !builtin)
	{
		ft_printf("FORK\n");
		sh->pipe->redir_fork = 1;
		sh->pipe->pid = fork_wrap();
		if (sh->pipe->pid != 0)
		{
			sh->pipe->redir_fork = 0;
			// set_process_group(sh, sh->pipe->pid);
			update_fg_job(sh, sh->pipe->pid, get_cmd_name((t_treenode *)node));
			wait_for_job(sh, sh->pipe->pid);
		}
	}
	if (sh->pipe->pid == 0 || builtin)
	{
		if (!builtin)
			ft_signal_dfl();
		if (open_file(node, terminal, sh, &fd))
			return ;
		sh->pipe->previous_redir[fd] = 1;
		cpy = dup(node->close_fd);
		sh->pipe->previous_redir[cpy] = 1;
		if (sh->pipe->previous_redir[node->close_fd] == 1)
			sh->pipe->previous_redir[node->close_fd] = 0;
		sh->pipe->write_fd = fd;
		sh->pipe->close_fd = node->close_fd;
		if (dup2(fd, node->close_fd) < 0)
			exit_error(sh, 1, "exec_redir dup2 failed");
		if (node->close_fd == STDOUT_FILENO)
			sh->pipe->redir_out = 1;
		else if (node->close_fd == STDIN_FILENO)
			sh->pipe->redir_in = 1;
		if (sh->pipe->write_pipe[1] > 0 && node->close_fd == STDOUT_FILENO)
		{
			close(sh->pipe->write_pipe[1]);
			sh->pipe->write_pipe[1] = -1;
		}
		exec_tree(node->cmd, environ_cp, terminal, sh);
		sh->pipe->redir_fork = 0;
	}
	// sh->pipe->close_fd = -1;
	// sh->pipe->write_fd = -1;
	// if (dup2(cpy, node->close_fd) < 0)
	// 	exit_error(sh, 1, "exec_redir dup2 failed");
}
