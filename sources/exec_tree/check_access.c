/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:50:23 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/25 03:06:52 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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
		if (ft_env_get(sh, "PATH", sh->env))
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
