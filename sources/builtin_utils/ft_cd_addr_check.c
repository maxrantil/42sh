/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_addr_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:27:40 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/23 14:14:35 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*build_real_path(char *file)
{
	char	cwd[1024];
	char	*ret;

	getcwd(cwd, 1024);
	ret = ft_strjoin_three(cwd, "/", file);
	return (ret);
}

void	manipulate_env(t_shell *session, char *file)
{
	char	**list;

	if (file[0] != '/')
		file = build_real_path(file);
	else
		file = ft_strdup(file);
	file = trim_dots(file, 0);
	if (chdir(file) != -1)
	{
		list = (char **)malloc(sizeof(char *) * 3);
		if (!list)
			exit(1);
		list[0] = ft_strjoin("PWD=", file);
		list[1] = ft_strjoin("PWD=", file);
		list[2] = NULL;
		ft_export(session, list, 0);
		ft_arrclean(list);
	}
	ft_memdel((void *)&file);
}

static int	handle_option_l(char *file, t_shell *session)
{
	struct stat	buff;

	if (file[ft_strlen(file) - 1] == '/' && !ft_strequ("/", file))
		file[ft_strlen(file) - 1] = '\0';
	if (lstat(file, &buff))
		return (ft_err_print(file, "cd", "No such file or directory", 1));
	if (S_ISLNK(buff.st_mode))
	{
		stat(file, &buff);
		if (S_ISDIR(buff.st_mode))
			manipulate_env(session, file);
		return (1);
	}
	else
	{
		stat(file, &buff);
		if (!S_ISDIR(buff.st_mode))
			return (ft_err_print(file, "cd", "Not a directory", 1));
		else if (access(file, X_OK))
			return (ft_err_print(file, "cd", "Permission denied", 1));
	}
	return (0);
}

/**
 * It checks if the file is a directory and if it has the right permissions
 *
 * @param file the file to check
 */

int	ft_cd_addr_check(char *file, int p_option, t_shell *session)
{
	struct stat	buff;

	if (p_option == 0)
		return (handle_option_l(file, session));
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
