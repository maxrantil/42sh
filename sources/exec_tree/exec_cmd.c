/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:35:18 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/17 12:24:32 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

static void	child_execute(char **cmd, t_cmdnode *head, \
int access, char ***environ_cp)
{
	if (access)
	{
		ft_signal_dfl();
		if (!g_sh->pipe->redir_out && g_sh->pipe->write_pipe[1] >= 0 \
		&& dup2(g_sh->pipe->write_pipe[1], STDOUT_FILENO) < 0)
		{
			ft_err_print("dup2", NULL, "failed", 2);
			exit(1);
		}
		if (!cmd || execve(*cmd, head->cmd, *environ_cp) < 0)
			exe_fail(cmd, head->cmd, environ_cp);
		exit(1);
	}
	else
		exit(127);
}

static void	ft_execve(char **cmd, t_cmdnode *head, \
int access, char ***environ_cp)
{
	int		pid;

	pid = fork_wrap();
	if (g_sh->pipe->pid == 0)
		g_sh->pipe->pid = pid;
	if (pid)
		update_fg_job(g_sh, pid, head->cmd);
	if (pid == 0)
		child_execute(cmd, head, access, environ_cp);
	wait_for_job(g_sh, pid);
}

void	exec_cmd(t_cmdnode *head, char ***environ_cp, t_shell *sh)
{
	char	*cmd;
	int		access;
	int		hash;

	if (!head->cmd[0])
		return ;
	if (!ft_builtins(sh, &head->cmd, environ_cp))
		return ;
	hash = 0;
	cmd = hash_check(sh, head->cmd[0], &hash);
	if (!hash && !check_if_user_exe(head->cmd[0], &cmd))
		cmd = search_bin(head->cmd[0], *environ_cp);
	access = check_access(cmd, head->cmd, sh);
	ft_execve(&cmd, head, access, environ_cp);
	if (access)
	{
		if (!hash)
			hash_init_struct(sh, cmd, 1);
	}
	ft_memdel((void **)&cmd);
}
