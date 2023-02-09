/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/08 15:49:00 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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
	else if (!ft_strcmp(**cmd, "fg"))
		return (ft_fg(sh, *cmd));
	else if (!ft_strcmp(**cmd, "bg"))
		return (ft_bg(sh, *cmd));
	else if (!ft_strcmp(**cmd, "jobs"))
		return (ft_jobs(sh));
	else if (!ft_strcmp(**cmd, "type"))
		return (type_command(sh, *cmd, *environ_cp));
	return (1);
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
int	ft_builtins(t_shell *sh, char ***cmd, char ***environ_cp)
{
	if (sh && cmd)
	{
		ft_env_last_command(sh, *cmd);
		if (param_format(*cmd) == -1)
			return (0);
		ft_expansion(sh, *cmd);
		*(cmd) += ft_variables(sh, cmd);
		return (cmd_comparisons(sh, cmd, environ_cp));
	}
	return (1);
}
