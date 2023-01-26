/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:57:49 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/26 09:56:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It swaps the current working directory with the PWD environment variable
 *
 * @param sh The session struct.
 * @param cwd the current working directory
 */
static void	swap_pwd(t_shell *sh, char *cwd)
{
	char	**pwd;
	char	*new_pwd;

	pwd = ft_env_get(sh, "PWD");
	new_pwd = ft_strjoin("PWD=", cwd);
	if (pwd)
	{
		ft_strdel(pwd);
		*pwd = new_pwd;
	}
	else
	{
		ft_env_append(sh, &new_pwd);
		ft_strdel(&new_pwd);
	}
}

/**
 * It swaps the values of the PWD and OLDPWD environment variables
 *
 * @param sh the session struct
 */
static void	swap_oldpwd(t_shell *sh)
{
	char	**pwd;
	char	**oldpwd;

	pwd = ft_env_get(sh, "PWD");
	oldpwd = ft_env_get(sh, "OLDPWD");
	if (oldpwd && pwd)
	{
		ft_strdel(oldpwd);
		*oldpwd = ft_strjoin("OLDPWD", ft_strchr(*pwd, '='));
	}
}

/**
 * It swaps the current working directory and swaps the PWD env varriable
 * with the new path and updates the with the OLDPWD.
 *
 * @param sh the session struct
 */
void	ft_dir_change(t_shell *sh)
{
	char	*oldpwd;
	char	cwd[BUFF_SIZE];

	oldpwd = "OLDPWD=";
	if (!ft_env_get(sh, "OLDPWD"))
		ft_env_append(sh, &oldpwd);
	swap_oldpwd(sh);
	swap_pwd(sh, getcwd(cwd, sizeof(cwd)));
}
