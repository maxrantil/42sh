/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_symlink_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:30:31 by spuustin          #+#    #+#             */
/*   Updated: 2023/02/23 14:14:46 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	is_path_symlink(char *path)
{
	struct stat	buff;
	struct stat	buff_two;

	if (lstat(path, &buff))
		return (ft_err_print(path, "cd", "No such file or directory", 1));
	if (S_ISLNK(buff.st_mode))
	{
		if (!stat(path, &buff_two))
		{
			if (S_ISDIR(buff_two.st_mode))
				if (!access(path, X_OK))
					return (1);
		}
	}
	return (0);
}

int	cd_minus_symlink(t_shell *sh, char *path)
{
	char	**pwd;
	char	**oldpwd;
	char	**list;

	list = (char **)malloc(sizeof(char *) * 3);
	if (!list)
		exit(1);
	pwd = ft_env_get(sh, "PWD", sh->env);
	oldpwd = ft_env_get(sh, "OLDPWD", sh->env);
	if (chdir(path) == -1)
		exit(1);
	if (oldpwd && pwd)
	{
		ft_strdel(oldpwd);
		*oldpwd = ft_strjoin("OLDPWD", ft_strchr(*pwd, '='));
	}
	list[0] = ft_strjoin("PWD=", path);
	list[1] = ft_strjoin("PWD=", path);
	list[2] = NULL;
	ft_printf("%s\n", path);
	ft_export(sh, list, 0);
	ft_arrclean(list);
	ft_memdel((void *)&path);
	return (1);
}

void	erase_last_subdir(char *path)
{
	int		idx;

	idx = ft_strlen(path) - 1;
	if (path[idx] == '/')
		idx--;
	while (path[idx])
	{
		if (path[idx] == '/')
		{
			path[idx + 1] = '\0';
			break ;
		}
		idx--;
	}
}

int	resolve_dotdot_symlink(t_shell *sh, char **cmd)
{
	char	*path;

	if (ft_strequ(cmd[ft_arrlen(cmd) - 1], ".."))
	{
		path = env_path(sh, "PWD");
		if (path && ft_strequ(path, "/"))
			return (cd_symlink_utils_free(&path, 1));
		if (sh->is_flag_on == 0)
		{
			erase_last_subdir(path);
			if (chdir(path) == -1)
				exit(1);
			ft_chdir_expanded(sh, &path);
		}
		else
		{
			if (chdir(path) == -1 || chdir("..") == -1)
				exit(1);
			ft_dir_change(sh);
		}
		return (cd_symlink_utils_free(&path, 0));
	}
	return (1);
}

void	reset_options(t_shell *sh)
{
	sh->option_count = 0;
	sh->is_flag_on = 0;
	sh->arr_len = 0;
}
