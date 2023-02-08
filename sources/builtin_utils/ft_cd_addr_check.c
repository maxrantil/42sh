/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_addr_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:27:40 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/08 19:07:40 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*trim_dots(char *path, int i, int to_skip, char *trimmed)
{
	char	**sub_dirs;

	sub_dirs = ft_strsplit(path, '/');
	if (!sub_dirs)
		exit(1);
	trimmed = trim_dots_helper(sub_dirs, trimmed, i, to_skip);
	ft_arrclean(sub_dirs);
	ft_memdel((void *)&path);
	return (trimmed);
}

static char	*build_real_path(char *file)
{
	char	cwd[1024];
	char	*ret;

	getcwd(cwd, 1024);
	ret = ft_strjoin_three(cwd, "/", file);
	ret = trim_dots(ret, 0, 0, NULL);
	return (ret);
}

static void	manipulate_env(t_shell *session, char *file)
{
	char	**list;

	if (file[0] != '/')
		file = build_real_path(file);
	if (chdir(file) != -1)
	{
		list = (char **)malloc(sizeof(char *) * 3);
		if (!list)
			exit(1);
		list[0] = ft_strjoin("PWD=", file);
		list[1] = ft_strjoin("PWD=", file);
		list[2] = NULL;
		ft_export(session, list);
		ft_arrclean(list);
	}
}

static int	handle_option_l(char *file, t_shell *session)
{
	struct stat	buff;

	if (lstat(file, &buff))
		return (ft_err_print(file, "cd", "No such file or directory", 1));
	if (S_ISLNK(buff.st_mode))
	{
		stat(file, &buff);
		if (S_ISDIR(buff.st_mode))
			manipulate_env(session, file);
	}
	else
	{
		stat(file, &buff);
		if (!S_ISDIR(buff.st_mode))
			return (ft_err_print(file, "cd", "Not a directory", 1));
		else if (access(file, X_OK))
			return (ft_err_print(file, "cd", "Permission denied", 1));
		if (chdir(file) == -1)
			write(2, "42sh: cd: chdir failed.\n", 25);
	}
	return (1);
}

/**
 * It checks if the file is a directory and if it has the right permissions
 *
 * @param file the file to check
 */

int	ft_cd_addr_check(char *file, int p_option, t_shell *session)
{
	struct stat	buff;
	int			ret;

	if (p_option == 0)
		ret = handle_option_l(file, session);
	if (stat(file, &buff))
		return (ft_err_print(file, "cd", "No such file or directory", 1));
	else
	{
		if (!S_ISDIR(buff.st_mode))
			return (ft_err_print(file, "cd", "Not a directory", 1));
		else if (access(file, X_OK))
			return (ft_err_print(file, "cd", "Permission denied", 1));
	}
	return (0);
}
