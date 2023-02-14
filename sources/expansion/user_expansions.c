/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:24:20 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/13 20:49:59 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	is_valid_user(char *input, char *name)
{
	if (ft_strcmp(&input[1], name) == 0 && input[0] != '.' && input[1] != '.')
		return (1);
	return (0);
}

static char	*init_user_exp(char *str, char **user, DIR **dir, char **temp)
{
	(*temp) = NULL;
	if (!str[1] || str[1] == '/')
	{
		closedir(*dir);
		return (NULL);
	}
	(*temp) = ft_strchr(str, '/');
	if ((*temp))
	{
		(*temp) = ft_strdup((*temp));
		(*user) = ft_strndup(str, ft_strlen(str) - ft_strlen((*temp)));
	}
	else
	{
		(*user) = ft_strdup(str);
		(*temp) = ft_strnew(1);
	}
	return ((*temp));
}

int	init_dir_open(DIR **dir, struct dirent **entity, char **path)
{
	*dir = opendir("/Users");
	*path = NULL;
	if (*dir == NULL)
		return (0);
	*entity = readdir(*dir);
	return (1);
}

char	*user_expansions(char *str)
{
	DIR				*dir;
	struct dirent	*entity;
	char			*path;
	char			*user;
	char			*temp;

	if (!init_dir_open(&dir, &entity, &path))
		return (NULL);
	if (!init_user_exp(str, &user, &dir, &temp))
		return (NULL);
	while (entity != NULL)
	{
		if (is_valid_user(user, entity->d_name))
		{
			closedir(dir);
			join_paths((&user), &temp, &path, 1);
			return (path);
		}
		entity = readdir(dir);
	}
	closedir(dir);
	join_paths(&user, &temp, &path, 0);
	return (path);
}
