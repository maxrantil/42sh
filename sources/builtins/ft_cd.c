/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:10:09 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/01 20:54:02 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	ft_chdir_expanded(t_session *sesh, char **path)
{
	chdir(*path);
	ft_dir_change(sesh);
	ft_strdel(path);
	return (1);
}

static int	ft_cd_expand_error(char **cmd)
{
	if (!*(cmd + 1) || !ft_strcmp(*(cmd + 1), "--"))
		ft_err_print(NULL, "cd", "HOME not set", 1);
	else if (!ft_strcmp(*(cmd + 1), "~-") || !ft_strcmp(*(cmd + 1), "-"))
		ft_err_print(NULL, "cd", "OLDPWD not set", 1);
	return (1);
}

static char	*env_path(t_session *sesh, char *key)
{
	char	**env;
	char	*path;

	env = ft_env_get(sesh, key);
	if (env)
		path = ft_strdup(ft_strchr(*env, '=') + 1);
	else
		path = NULL;
	return (path);
}

static int	ft_cd_expand(t_session *sesh, char **cmd, char **path)
{
	int		ret;
	ret = 0;
	if (ft_arrlen(cmd) == 1 || !ft_strcmp(*(cmd + sesh->option_count + 1), "--"))
	{
		*path = env_path(sesh, "HOME");
		ret = 1;
	}
	else if (!ft_strcmp(*(cmd + 1), "-"))
	{
		*path = env_path(sesh, "OLDPWD");
		if (*path)
			ft_putendl(ft_strchr(*ft_env_get(sesh, "OLDPWD"), '=') + 1);
		ret = 1;
	}
	if (*path)
		return (ft_chdir_expanded(sesh, path));
	else if (ret || !ft_strcmp(*(cmd + 1), "~-"))
		return (ft_cd_expand_error(cmd));
	return (0);
}

/**
 * It changes the current working directory to the one specified by the user, 
 * or to the home directory if no directory is specified.
 * 
 * @param sesh a pointer to the session struct
 * @param cmd The command line arguments.
 * 
 * @return 0
 */

// for now we assume -L or -- etc arent names of directories

static int	cd_multi_command_validation(t_session *sesh, char **commands)
{
	if (commands[1][0] != '-')
	{
		ft_err_print(NULL, "cd", "too many arguments", 1);
		sesh->exit_stat = 1;
		return (1);
	}
	if (validate_cd_options(sesh, commands) == 1)
	{

		sesh->exit_stat = 1;
		return (1);
	}
	return (0);
}

int	ft_cd(t_session *sesh, char **cmd)
{
	char	*path;

	path = NULL;
	sesh->exit_stat = 0;
	if (ft_arrlen(cmd) > 2)
	{
		if (cd_multi_command_validation(sesh, cmd) == 1)
			return (0);
	}
	if (!ft_cd_expand(sesh, cmd, &path) && !ft_cd_addr_check(*(cmd + sesh->option_count + 1), sesh->is_flag_on, sesh))
	{
		if (chdir(*(cmd + sesh->option_count + 1)))
			sesh->exit_stat = 1;
		else
			ft_dir_change(sesh);
	}
	else
		sesh->exit_stat = 1;
	sesh->option_count = 0;
	sesh->is_flag_on = 0;
	return (0);
}
