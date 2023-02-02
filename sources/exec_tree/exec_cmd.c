/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:12:53 by jakken            #+#    #+#             */
/*   Updated: 2023/02/02 17:09:42 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

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

static int	ft_execve(char **cmd, t_cmdnode *head, int access, char ***environ_cp)
{
	int		status;
	int		pid;
	char	**args;

	args = head->cmd;
	status = 0;
	pid = -1;
	if (access)
	{
		pid = fork_wrap();
		if (pid)
			update_fg_job(g_sh, pid, args);
		if (pid == 0)
		{
			ft_signal_dfl();
			if (g_sh->pipe->pipefd[1] >= 0 && dup2(g_sh->pipe->pipefd[1], STDOUT_FILENO) < 0)
			{
				ft_err_print("dup2", NULL, "failed", 2);
				exit(1);
			}
			if (!cmd || execve(*cmd, args, *environ_cp) < 0)
				exe_fail(cmd, args, environ_cp);
			exit(1);
		}
		if (g_sh->ampersand)
			waitpid(pid, &status, WNOHANG);
		else
			waitpid(pid, &status, WUNTRACED);
	}
	return (status);
}

void	exec_cmd(t_cmdnode *head, char ***environ_cp, t_shell *sh)
{
	char	*cmd;
	int		access;
	int		status;
	int		hash;
	char	**args;

	args = head->cmd;
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
	status = ft_execve(&cmd, head, access, environ_cp);
	if (access)
	{
		sh->exit_stat = status >> 8;
		if (!hash)
			hash_init_struct(sh, cmd, 1);
	}
	ft_memdel((void **)&cmd);
}
