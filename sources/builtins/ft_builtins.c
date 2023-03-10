/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:53:04 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/25 01:14:26 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	cmd_comparisons_continue(t_shell *sh, char ***cmd, \
										char ***environ_cp)
{
	if (!ft_strcmp(**cmd, "test"))
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
		return (ft_jobs(sh, *cmd));
	else if (!ft_strcmp(**cmd, "type"))
		return (type_command(sh, *cmd, *environ_cp, 1));
	else if (!ft_strcmp(**cmd, "unalias"))
		return (unalias(sh, *cmd));
	else if (!ft_strcmp(**cmd, "alias"))
		return (alias(sh, *cmd));
	return (1);
}

int	cmd_comparisons(t_shell *sh, char ***cmd, char ***environ_cp)
{
	if (**cmd == NULL)
		return (0);
	if (!ft_strcmp(**cmd, "fc"))
		return (ft_fc(sh, cmd));
	if (!ft_strcmp(**cmd, "set"))
		return (ft_set(sh, cmd));
	else if (!ft_strcmp(**cmd, "export"))
		return (ft_export(sh, *cmd, 0));
	else if (!ft_strcmp(**cmd, "unset"))
		return (ft_unset(sh, *cmd));
	else if (!ft_strcmp(**cmd, "cd"))
		return (ft_cd(sh, *cmd));
	else if (!ft_strcmp(**cmd, "echo"))
		return (ft_echo(sh, *cmd));
	else if (!ft_strcmp(**cmd, "history"))
		return (ft_history(sh->term, *cmd));
	else
		return (cmd_comparisons_continue(sh, cmd, environ_cp));
	return (1);
}

int	is_builtin(char **cmd)
{
	char	*str;

	str = lower_case(*cmd);
	if (!ft_strcmp(str, "set") || !ft_strcmp(str, "export") \
	|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "cd") \
	|| !ft_strcmp(str, "echo") || !ft_strcmp(str, "exit") \
	|| !ft_strcmp(str, "hash") || !ft_strcmp(str, "history") \
	|| !ft_strcmp(str, "test") || !ft_strcmp(str, "fc") \
	|| !ft_strcmp(str, "fg") || !ft_strcmp(str, "bg") \
	|| !ft_strcmp(str, "jobs") || !ft_strcmp(str, "type") \
	|| !ft_strcmp(str, "alias") || !ft_strcmp(str, "unalias"))
	{
		ft_strdel(cmd);
		*cmd = str;
		return (1);
	}
	ft_strdel(&str);
	return (0);
}

int	ft_builtins(t_shell *sh, char ***cmd, char ***environ_cp)
{
	if (sh && cmd)
	{
		ft_env_last_command(sh, *cmd);
		if (param_format(*cmd) == -1)
			return (0);
		ft_expansion(sh, *cmd);
		if (!***cmd)
			return (0);
		if (!ft_variables(sh, cmd))
			return (0);
		if (**cmd && !is_builtin(*cmd))
			return (1);
		if (!fork_if_pipe(sh, cmd, environ_cp))
			return (cmd_comparisons(sh, cmd, environ_cp));
		else
			return (0);
	}
	return (1);
}
