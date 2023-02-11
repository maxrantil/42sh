/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_addr_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:27:40 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/11 12:54:32 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"


//we reverse path till we find second '/'
static int	skip_sub_dir(char *path, int i)
{
	int		slashes;

	slashes = 0;
	while(slashes < 2 && i >= 0)
	{
		if (path[i] == '/')
			slashes++;
		i--;
	}
	return (i + 1);
}

static void trim_dot_dot_slash(char *path)
{
	int i = 0;
	int idx;
	while(path[i])
	{
		if (path[i] && path[i + 1] && path[i + 2] && path[i] == '.' 
		&& path[i + 1] == '.' && path[i + 2] == '/')
		{
			idx = skip_sub_dir(path, i);
			int	len = ft_strlen(path + i + 2);
			ft_memmove(&path[idx], &path[i + 2], len);
			path[idx + len] = '\0';
			i = idx;
		}
		i++;
	}
}

static char	*trim_dots(char *file, int i, int to_skip, char *trimmed)
{
	size_t	post_len;
	//int		idx;
	(void)to_skip;
	(void)trimmed;
	i = 0;
	char *path = ft_strdup(file);
	while (path[i])
	{
		if (path[i] && path[i + 1] && path[i] == '.' && path[i + 1] == '/' && path[i - 1] && path[i - 1] != '.')
		{
			post_len = ft_strlen(&(path[i]));
			ft_memmove(&path[i], &path[i + 2], post_len);
			path[i + post_len] = '\0';
			i--;
		}
		i++;
	}
	trim_dot_dot_slash(path);
	return(path);
}

static char	*build_real_path(char *file)
{
	char	cwd[1024];
	char	*ret;

	getcwd(cwd, 1024);
	ret = ft_strjoin_three(cwd, "/", file);
	return (ret);
}

static void	manipulate_env(t_shell *session, char *file)
{
	char	**list;

	if (file[0] != '/')
		file = build_real_path(file);
	else
		file = ft_strdup(file);
	file = trim_dots(file, 0, 0, NULL);
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
	ft_memdel((void *)&file);
}

static int	handle_option_l(char *file, t_shell *session)
{
	struct stat	buff;

	//file = trim_dots(file, 0, 0, NULL);
	if (file[ft_strlen(file) - 1] == '/')
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
