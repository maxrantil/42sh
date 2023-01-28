/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:12:53 by jakken            #+#    #+#             */
/*   Updated: 2023/01/28 16:41:32 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell *g_sh;

int	check_if_user_exe(char *cmd, char **dest)
{
	*dest = NULL;
	if (ft_strchr(cmd, '/'))
	{
		*dest = ft_strdup(cmd);
		return (1);
	}
	return (0);
}

static int	check_file_validity(struct stat *buff, char *cmd)
{
	if (S_ISDIR(buff->st_mode))
	{
		ft_err_print(NULL, cmd, "Is a directory", 2);
		return (0);
	}
	else if (access(cmd, X_OK) < 0)
	{
		ft_err_print(NULL, cmd, "Permission denied", 2);
		return (0);
	}
	return (1);
}

int	check_access(char *cmd, char **args, t_shell *sh)
{
	struct stat	buf;

	if (((cmd && ft_strchr(cmd, '/')) && access(cmd, F_OK) < 0))
	{
		ft_err_print(NULL, args[0], "No such file or directory", 2);
		sh->exit_stat = 127;
		return (0);
	}
	else if (!cmd || !ft_strchr(cmd, '/'))
	{
		if (ft_env_get(sh, "PATH"))
			ft_err_print(NULL, args[0], "command not found", 2);
		else
			ft_err_print(NULL, args[0], "No such file or directory", 2);
		sh->exit_stat = 127;
		return (0);
	}
	stat(cmd, &buf);
	if (!check_file_validity(&buf, cmd))
	{
		sh->exit_stat = 126;
		return (0);
	}
	return (1);
}

static void	print_args(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

static int	ft_execve(char **cmd, char **args, int access, char ***environ_cp)
{
	int		status;
	int		pid;

	status = 0;
	pid = -1;
	if (access)
	{
		pid = fork_wrap();
		if (pid == 0)
		{
			if (!cmd || execve(*cmd, args, *environ_cp) < 0)
				exe_fail(cmd, args, environ_cp);
			exit (1);
		}
	}
	wait(&status);
		// ft_putstr_fd("PID_BEFORE: ", 2);
		// ft_putnbr_fd(pid, 2);
		// ft_putstr_fd("\n", 2);
		// ft_putstr_fd(*cmd, 2);
		// ft_putstr_fd("\n", 2);
	// Attach to shared memory segmetn
	attach_fg_grp();
	if (*g_sh->jobs->shared_mem_idx_ptr < JOBS_MAX)
		g_sh->jobs->shared_mem_ptr[(*g_sh->jobs->shared_mem_idx_ptr)++] = pid;
	// int i = 0;
		// ft_putstr_fd("\n", 2);
	// while (i < *g_sh->jobs->shared_mem_idx_ptr)
	// {
		// ft_putstr_fd("PID: ", 2);
		// ft_putnbr_fd(g_sh->jobs->shared_mem_ptr[i], 2);
		// ft_putstr_fd(" CMD: ", 2);
		// ft_putstr_fd(*cmd, 2);
		// ft_putstr_fd("\n", 2);
		// ++i;
	// }
		// ft_putstr_fd("\n", 2);
	detach_fg_grp();
	if (status & 0177)
		ft_putchar('\n');
	return (status);
}

void	exec_cmd(char **args, char ***environ_cp, t_shell *sh)
{
	char	*cmd;
	int		access;
	int		status;
	int		hash;

	if (!args[0])
		return ;
	if (sh->term->fc_flag)
		print_args(args);
	if (!ft_builtins(sh, &args))
		return ;
	hash = 0;
	cmd = hash_check(sh, args[0], &hash);
	if (!hash && !check_if_user_exe(args[0], &cmd))
		cmd = search_bin(args[0], *environ_cp);
	access = check_access(cmd, args, sh);
	status = ft_execve(&cmd, args, access, environ_cp);
	if (access)
	{
		sh->exit_stat = status >> 8;
		if (!hash)
			hash_init_struct(sh, cmd, 1);
	}
	ft_memdel((void **)&cmd);
}
