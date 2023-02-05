/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_addr_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:27:40 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/05 19:33:10 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

//add to libft
static char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	size_t	total;
	char	*new;

	if (!s1 || !s2 || !s3)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	new = ft_strnew(total);
	if (new != NULL)
	{
		new = ft_strcpy(new, (const char *)s1);
		new = ft_strcat(new, (const char *)s2);
		new = ft_strcat(new, (const char *)s3);
	}
	return (new);
}

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

static void	manipulate_env(t_session *session, char *file)
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
	ft_memdel((void *)&file);
}

static int	handle_option_l(char *file, t_session *session)
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

int	ft_cd_addr_check(char *file, int p_option, t_session *session)
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
