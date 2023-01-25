/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir_change.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:57:49 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/06 12:55:00 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It swaps the current working directory with the PWD environment variable
 * 
 * @param sesh The session struct.
 * @param cwd the current working directory
 */
static void	swap_pwd(t_session *sesh, char *cwd)
{
	char	**pwd;
	char	*new_pwd;

	pwd = ft_env_get(sesh, "PWD");
	new_pwd = ft_strjoin("PWD=", cwd);
	if (pwd)
	{
		ft_strdel(pwd);
		*pwd = new_pwd;
	}
	else
	{
		ft_env_append(sesh, &new_pwd);
		ft_strdel(&new_pwd);
	}
}

/**
 * It swaps the values of the PWD and OLDPWD environment variables
 * 
 * @param sesh the session struct
 */
static void	swap_oldpwd(t_session *sesh)
{
	char	**pwd;
	char	**oldpwd;

	pwd = ft_env_get(sesh, "PWD");
	oldpwd = ft_env_get(sesh, "OLDPWD");
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
 * @param sesh the session struct
 */
void	ft_dir_change(t_session *sesh)
{
	char	*oldpwd;
	char	cwd[BUFF_SIZE];

	oldpwd = "OLDPWD=";
	if (!ft_env_get(sesh, "OLDPWD"))
		ft_env_append(sesh, &oldpwd);
	swap_oldpwd(sesh);
	swap_pwd(sesh, getcwd(cwd, sizeof(cwd)));
}
