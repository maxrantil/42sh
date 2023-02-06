/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:12:50 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/26 09:56:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// static int	env_check_access(t_shell *sh, char *cmd, char **args)
// {
// 	struct stat	buf;

// 	if (!cmd || !ft_strchr(cmd, '/'))
// 	{
// 		ft_err_print(NULL, args[0], "No such file or directory", 2);
// 		sh->exit_stat = 127;
// 		return (0);
// 	}
// 	stat(cmd, &buf);
// 	if (S_ISDIR(buf.st_mode) || access(cmd, X_OK) == -1)
// 	{
// 		ft_err_print(cmd, NULL, "Permission denied", 2);
// 		sh->exit_stat = 126;
// 		return (0);
// 	}
// 	return (1);
// }

// static void	ft_env_execve(t_shell *sh, char **args, char ***environ_cp)
// {
// 	char	*cmd;

// 	if (!check_if_user_exe(args[0], &cmd))
// 		cmd = search_bin(args[0], *environ_cp);
// 	if (env_check_access(sh, cmd, args) && fork_wrap() == 0)
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
 * @param sh the session struct
 * @param cmd the command line arguments
 *
 * @return The return value of the last command executed.
 */
int	ft_set(t_shell *sh, char ***cmd)
{
	int	i;

	(void)cmd;
	i = -1;
	sh->exit_stat = 0;
	// if (*((*cmd) + i) && ft_strchr(*((*cmd) + i), '='))
	// 	i = ft_env_temp(sh, *cmd, i);
	// if (*((*cmd) + i))
	// {
	// 	ft_env_execve(sh, (*cmd + i), &sh->env);
	// 	return (0);
	// }
	while (*(sh->env + ++i))
		ft_putendl(*(sh->env + i));
	i = -1;
	while (*(sh->intr_vars + ++i))
		ft_putendl(*(sh->intr_vars + i));
	return (0);
}
