/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:12:50 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/25 15:30:45 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// static int	env_check_access(t_session *sesh, char *cmd, char **args)
// {
// 	struct stat	buf;

// 	if (!cmd || !ft_strchr(cmd, '/'))
// 	{
// 		ft_err_print(NULL, args[0], "No such file or directory", 2);
// 		sesh->exit_stat = 127;
// 		return (0);
// 	}
// 	stat(cmd, &buf);
// 	if (S_ISDIR(buf.st_mode) || access(cmd, X_OK) == -1)
// 	{
// 		ft_err_print(cmd, NULL, "Permission denied", 2);
// 		sesh->exit_stat = 126;
// 		return (0);
// 	}
// 	return (1);
// }

// static void	ft_env_execve(t_session *sesh, char **args, char ***environ_cp)
// {
// 	char	*cmd;

// 	if (!check_if_user_exe(args[0], &cmd))
// 		cmd = search_bin(args[0], *environ_cp);
// 	if (env_check_access(sesh, cmd, args) && fork_wrap() == 0)
// 	{
// 		if (!cmd || execve(cmd, args, *environ_cp) < 0)
// 			exe_fail(&cmd, args, environ_cp);
// 		exit (1);
// 	}
// 	ft_strdel(&cmd);
// 	wait (0);
// }

/**
 * It prints the environment, or executes a command with a temporary environment
 *
 * @param sesh the session struct
 * @param cmd the command line arguments
 *
 * @return The return value of the last command executed.
 */
int	ft_set(t_session *sesh, char ***cmd)
{
	int	i;

	(void)cmd;
	i = -1;
	sesh->exit_stat = 0;
	// if (*((*cmd) + i) && ft_strchr(*((*cmd) + i), '='))
	// 	i = ft_env_temp(sesh, *cmd, i);
	// if (*((*cmd) + i))
	// {
	// 	ft_env_execve(sesh, (*cmd + i), &sesh->env);
	// 	return (0);
	// }
	while (*(sesh->env + ++i))
		ft_putendl(*(sesh->env + i));
	i = -1;
	while (*(sesh->intr_vars + ++i))
		ft_putendl(*(sesh->intr_vars + i));
	return (0);
}
