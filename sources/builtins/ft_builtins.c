/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/11 11:33:07 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	cmd_comparisons(t_shell *sh, char ***cmd, char ***environ_cp);

static int fork_if_pipe(t_shell *sh, char ***cmd, char ***environ_cp)
{
	int pid;

	if (sh->pipe->piping)
	{
		pid = fork_wrap();
		if (sh->pipe->pid == 0)
			sh->pipe->pid = pid;
		if (pid)
			update_fg_job(sh, pid, *cmd);
		if (pid == 0)
		{
			ft_signal_dfl();
			if (!sh->pipe->redir_out && sh->pipe->write_pipe[1] >= 0 && dup2(sh->pipe->write_pipe[1], STDOUT_FILENO) < 0)
			{
				ft_err_print("dup2", NULL, "failed", 2);
				exit(1);
			}
			cmd_comparisons(sh, cmd, environ_cp);
			exit(1);
		}
		return (1);
	}
	return(0);
}

static int is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "set") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")\
		|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "exit")\
		|| !ft_strcmp(cmd, "hash") || !ft_strcmp(cmd, "history") || !ft_strcmp(cmd, "test")\
		|| !ft_strcmp(cmd, "fc") || !ft_strcmp(cmd, "fg") || !ft_strcmp(cmd, "bg")\
		|| !ft_strcmp(cmd, "jobs") || !ft_strcmp(cmd, "type") || !ft_strcmp(cmd, "alias")\
		|| !ft_strcmp(cmd, "unalias"))
		return (1);
	return (0);
}

static int	cmd_comparisons(t_shell *sh, char ***cmd, char ***environ_cp)
{
	if (**cmd == NULL)
		return (0);
	if (!ft_strcmp(**cmd, "fc"))
		ft_fc(sh, cmd);
	if (**cmd && !ft_strcmp(**cmd, "set"))
		return (ft_set(sh, cmd));
	else if (**cmd && !ft_strcmp(**cmd, "export"))
		return (ft_export(sh, *cmd));
	else if (**cmd && !ft_strcmp(**cmd, "unset"))
		return (ft_unset(sh, *cmd));
	else if (**cmd && !ft_strcmp(**cmd, "cd"))
		return (ft_cd(sh, *cmd));
	else if (**cmd && !ft_strcmp(**cmd, "echo"))
		return (ft_echo(sh, *cmd));
	else if (!ft_strcmp(**cmd, "history"))
		return (ft_history(sh->term, *cmd));
	else if (!ft_strcmp(**cmd, "test"))
		return (ft_test(sh, *cmd));
	else if (!ft_strcmp(**cmd, "hash"))
		return (ft_hash(sh, *cmd));
	else if (!ft_strcmp(**cmd, "exit"))
		return (ft_exit(sh, *cmd));
	else if (!ft_strcmp(**cmd, "fg")) //ADD TO IS_BUILTIN STARTING HERE
		return (ft_fg(sh, *cmd));
	else if (!ft_strcmp(**cmd, "bg"))
		return (ft_bg(sh, *cmd));
	else if (!ft_strcmp(**cmd, "jobs"))
		return (ft_jobs(sh));
	else if (!ft_strcmp(**cmd, "type"))
		return (type_command(sh, *cmd, *environ_cp));
	else if (!ft_strcmp(**cmd, "unalias"))
		return (unalias(sh, *cmd));
	else if (!ft_strcmp(**cmd, "alias"))
		return (alias(sh, *cmd));
	return (1);
}

int		ft_builtins(t_shell *sh, char ***cmd, char ***environ_cp)
{
	if (sh && cmd)
	{
		ft_env_last_command(sh, *cmd);
		if (param_format(*cmd) == -1)
			return (0);
		ft_expansion(sh, *cmd);
		*(cmd) += ft_variables(sh, cmd);
		if (**cmd && !is_builtin(**cmd))
			return (1);
		if(!fork_if_pipe(sh, cmd, environ_cp))
			return(cmd_comparisons(sh, cmd, environ_cp));
		else
			return(0);
	}
	return (1);
}
