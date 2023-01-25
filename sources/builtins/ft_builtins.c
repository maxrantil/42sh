/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/01/25 16:10:38 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "ft_21sh.h"

/**
 * It takes a session and a command, expands the command, and then checks if
 * the command is a builtin. If it is, it runs the builtin and returns the exit
 * status. If it's not, it returns 1.
 *
 * @param sesh the session struct
 * @param cmd The command to be executed.
 *
 * @return The return value of the builtin function.
 */
int	ft_builtins(t_session *sesh, char ***cmd)
{
	if (sesh && cmd)
	{
		ft_expansion(sesh, *cmd);
		if (param_format(sesh, *cmd) == -1)
			return (0);
		*(cmd) += ft_variables(sesh, cmd);
		if (**cmd == NULL)
			return (0);
		else if (**cmd && !ft_strcmp(**cmd, "set"))
			return (ft_set(sesh, cmd));
		else if (**cmd && !ft_strcmp(**cmd, "export"))
			return (ft_export(sesh, *cmd));
		else if (**cmd && !ft_strcmp(**cmd, "unset"))
			return (ft_unset(sesh, *cmd));
		else if (**cmd && !ft_strcmp(**cmd, "cd"))
			return (ft_cd(sesh, *cmd));
		else if (**cmd && !ft_strcmp(**cmd, "echo"))
			return (ft_echo(sesh, *cmd));
		else if (!ft_strcmp(**cmd, "history"))
			return (ft_history(sesh->term, *cmd));
		else if (!ft_strcmp(**cmd, "fc"))
			return (ft_fc(sesh, cmd));
		else if (!ft_strcmp(**cmd, "test"))
			return(ft_test(sesh, *cmd));
		else if (!ft_strcmp(**cmd, "hash"))
			return (ft_hash(sesh, *cmd));
		else if (!ft_strcmp(**cmd, "exit"))
			ft_exit(sesh, 0);
	}
	return (1);
}
