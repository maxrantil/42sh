/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:10:09 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/15 22:29:40 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*env_path(t_shell *sh, char *key)
{
	char	**env;
	char	*path;

	env = ft_env_get(sh, key, sh->env);
	if (env)
		path = ft_strdup(ft_strchr(*env, '=') + 1);
	else
		path = NULL;
	return (path);
}

int	ft_chdir_expanded(t_shell *sh, char **path)
{
	int ignore	__attribute__((unused));

	ignore = chdir(*path);
	ft_dir_change(sh);
	ft_strdel(path);
	return (1);
}

static int	ft_cd_expand_error(char **cmd)
{
	if (!*(cmd + 1) || !ft_strcmp(*(cmd + 1), "--"))
		ft_err_print(NULL, "cd", "HOME not set", 2);
	else if (!ft_strcmp(*(cmd + 1), "~-") || !ft_strcmp(*(cmd + 1), "-"))
		ft_err_print(NULL, "cd", "OLDPWD not set", 2);
	return (1);
}

static int	ft_cd_expand(t_shell *sh, char **cmd, char **path, int ret)
{
	sh->arr_len = ft_arrlen(cmd) - 1;
	if (ft_arrlen(cmd) - sh->option_count == 1 || \
	!ft_strcmp(*(cmd + sh->option_count + 1), "--"))
	{
		*path = env_path(sh, "HOME");
		ret = 1;
	}
	else if (!ft_strcmp(*(cmd + sh->arr_len), "-"))
	{
		*path = env_path(sh, "OLDPWD");
		if (*path && !sh->is_flag_on && is_path_symlink(*path))
		{
			return (cd_minus_symlink(sh, *path));
		}
		else if (*path)
			ft_putendl(ft_strchr(*ft_env_get(sh, "OLDPWD", sh->env), '=') + 1);
		else
			return (ft_err_print(NULL, "cd", "OLDPWD not set", 2));
		ret = 1;
	}
	if (*path)
		return (ft_chdir_expanded(sh, path));
	else if (ret || !ft_strcmp(*(cmd + sh->arr_len), "~-"))
		return (ft_cd_expand_error(cmd));
	return (0);
}

/**
 * It changes the current working directory to the one specified by the user,
 * or to the home directory if no directory is specified.
 *
 * @param sh a pointer to the shell struct
 * @param cmd The command line arguments.
 *
 * @return 0
 */

int	ft_cd(t_shell *sh, char **cmd)
{
	char	*path;

	path = NULL;
	sh->exit_stat = 0;
	if (cd_multi_command_validation(sh, cmd) == 1 || \
	!resolve_dotdot_symlink(sh, cmd))
	{
		reset_options(sh);
		return (0);
	}
	if (!ft_cd_expand(sh, cmd, &path, 0) && \
	!ft_cd_addr_check(*(cmd + sh->option_count + 1), sh->is_flag_on, sh))
	{
		if (chdir(*(cmd + sh->option_count + 1)))
			sh->exit_stat = 1;
		else
			ft_dir_change(sh);
	}
	else
		sh->exit_stat = 1;
	reset_options(sh);
	return (0);
}
