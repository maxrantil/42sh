/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:24:20 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/13 16:33:08 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	is_valid_user(char *input, char *name)
{
	if (ft_strcmp(&input[1], name) == 0 && input[0] != '.' && input[1] != '.')
		return (1);
	return (0);
}

char	*user_expansions(char *str)
{
	DIR				*dir;
	struct dirent	*entity;
	char			*path;
	char			*temp;
	char			*user;

	dir = opendir("/Users");
	temp = ft_strrchr(str, '/');
	if (temp)
		user = ft_strndup(str, ft_strlen(str) - ft_strlen(temp));
	else
		user = ft_strdup(str);
	path = NULL;
	if (dir == NULL)
		return (NULL);
	entity = readdir(dir);
	while (entity != NULL)
	{
		if (is_valid_user(user, entity->d_name))
		{
			path = ft_strjoin("/Users/", &user[1]);
			closedir(dir);
			ft_strdel(&user);
			if (temp)
				user = ft_strjoin(path, temp);
			else
				user = ft_strdup(path);
			ft_strdel(&path);	
			path = ft_strdup(user);
			ft_strdel(&user);
			return (path);
		}
		entity = readdir(dir);
	}
	closedir(dir);
	path = passwd_user(user);
	ft_strdel(&user);
	if (temp)
		user = ft_strjoin(path, temp);
	else
		user = ft_strdup(path);
	ft_strdel(&path);	
	path = ft_strdup(user);
	ft_strdel(&user);
	return (path);
}
