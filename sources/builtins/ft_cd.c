/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:10:09 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/15 14:18:00 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	is_path_symlink(char *path)
{
	struct stat	buff;

	if (lstat(path, &buff))
		return (ft_err_print(path, "cd", "No such file or directory", 1));
	if (S_ISLNK(buff.st_mode))
	{
		ft_printf("SIMO: %s is link!\n", path);
		if (stat(path, &buff))
		{
			if (S_ISDIR(buff.st_mode))
				if (!access(path, X_OK))
					return (1);
		}
	}
	else
		ft_printf("SIMO: %s ei ole linkki!\n", path);
	return (0);
}

static char	*env_path(t_shell *sh, char *key)
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

static int	ft_chdir_expanded(t_shell *sh, char **path)
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
		ft_err_print(NULL, "cd", "HOME not set", 1);
	else if (!ft_strcmp(*(cmd + 1), "~-") || !ft_strcmp(*(cmd + 1), "-"))
		ft_err_print(NULL, "cd", "OLDPWD not set", 1);
	return (1);
}

static int	ft_cd_expand(t_shell *sh, char **cmd, char **path)
{
	int		ret;

	ret = 0;
	//ft_printf("SIMO: cd_expand()\n");
	if (ft_arrlen(cmd) - sh->option_count == 1 || \
	!ft_strcmp(*(cmd + sh->option_count + 1), "--"))
	{
		*path = env_path(sh, "HOME");
		ret = 1;
	}
	else if (!ft_strcmp(*(cmd + 1), "-"))
	{
		*path = env_path(sh, "OLDPWD");
		if (*path)
			ft_putendl(ft_strchr(*ft_env_get(sh, "OLDPWD", sh->env), '=') + 1);
		ret = 1;
	}
	if (*path)
		return (ft_chdir_expanded(sh, path));
	else if (ret || !ft_strcmp(*(cmd + 1), "~-"))
		return (ft_cd_expand_error(cmd));
	return (0);
}

// void	erase_last_subdir(char *path)
// {
// 	int		idx;
	
// 	idx = ft_strlen(path) - 1;
// 	if (path[idx] == '/')
// 		idx--;
// 	while (path[idx])
// 	{
// 		if (path[idx] == '/')
// 		{
// 			path[idx + 1] = '\0';
// 			break ;
// 		}
// 		idx--;
// 	}
// }

// int	resolve_symlink(t_shell *sh, char **cmd)
// {
// 	char	*path;
// 	char	cwd[1024];

// 	if (ft_strequ(cmd[ft_arrlen(cmd) - 1], ".."))
// 	{
// 		path = env_path(sh, "PWD");
// 		if (path && ft_strequ(path, "/"))
// 			return (1);
// 		if (sh->is_flag_on == 0)
// 		{
// 			ft_printf("SIMO: -P ei ole paalla!\n");
// 			ft_printf("path oli: %s\n", path);
// 			erase_last_subdir(path);
// 			ft_printf("path on: %s\n", path);
// 			if (chdir(path) == -1)
// 				exit(1);
// 			ft_chdir_expanded(sh, &path);
// 		}
// 		else
// 		{
// 			ft_printf("SIMO: -P on paalla!\n");
// 			ft_printf("path on: %s\n", path);
// 			if (chdir(path) == -1 || chdir("..") == -1)
// 				exit(1);
// 			getcwd(cwd, 1024);
// 			ft_dir_change(sh);
// 		}
// 		ft_memdel((void *)&path);
// 		return (0);
// 	}
// 	else if (ft_strequ(cmd[ft_arrlen(cmd) - 1], "-"))
// 	{
// 		ft_printf("SIMO: going to cd -\n");
// 		// jos $oldpwd == symlink
// 		// 
// 	}
// 	ft_memdel((void *)&path);
// 	return (1);
// }

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
	if (cd_multi_command_validation(sh, cmd) == 1)
		return (0);
	// if (!resolve_symlink(sh, cmd))
	// 	return (0);
	if (!ft_cd_expand(sh, cmd, &path) && \
	!ft_cd_addr_check(*(cmd + sh->option_count + 1), sh->is_flag_on, sh))
	{
		if (chdir(*(cmd + sh->option_count + 1)))
			sh->exit_stat = 1;
		else
			ft_dir_change(sh);
	}
	else
		sh->exit_stat = 1;
	sh->option_count = 0;
	sh->is_flag_on = 0;
	return (0);
}
