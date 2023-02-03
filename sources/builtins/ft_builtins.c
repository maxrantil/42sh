/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/03 18:40:34 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void fork_if_pipe(t_shell *sh)
{
	if (sh->pipe->pipefd[0] >= 0)
	{
		sh->pipe->pid = fork_wrap();
		if (sh->pipe->pid == 0)
		{
			if (!sh->pipe->redirecting && sh->pipe->pipefd[1] >= 0 && dup2(sh->pipe->pipefd[1], STDOUT_FILENO) < 0)
			{
				ft_err_print("dup2", NULL, "failed", 2);
				exit(1);
			}
		}
	}
}


static int is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "set") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")\
		|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "exit")\
		|| !ft_strcmp(cmd, "hash") || !ft_strcmp(cmd, "history") || !ft_strcmp(cmd, "test")\
		|| !ft_strcmp(cmd, "fc"))
		return (1);
	return (0);
}

/**
 * It takes a session and a command, expands the command, and then checks if
 * the command is a builtin. If it is, it runs the builtin and returns the exit
 * status. If it's not, it returns 1.
 *
 * @param sh the session struct
 * @param cmd The command to be executed.
 *
 * @return The return value of the builtin function.
 */
int	ft_builtins(t_shell *sh, char ***cmd)
{
	if (sh && cmd)
	{
		ft_expansion(sh, *cmd);
		ft_env_last_command(sh, *cmd);
		if (param_format(sh, *cmd) == -1)
			return (0);
		*(cmd) += ft_variables(sh, cmd);
		if (**cmd && !is_builtin(**cmd))
			return (1);
		fork_if_pipe(sh);
		if (**cmd == NULL)
			return (0);
		else if (**cmd && !ft_strcmp(**cmd, "set"))
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
		else if (!ft_strcmp(**cmd, "fc"))
			return (ft_fc(sh, cmd));
		else if (!ft_strcmp(**cmd, "test"))
			return(ft_test(sh, *cmd));
		else if (!ft_strcmp(**cmd, "hash"))
			return (ft_hash(sh, *cmd));
		else if (!ft_strcmp(**cmd, "exit"))
			ft_exit(sh, 0);
	}
	return (1);
}
