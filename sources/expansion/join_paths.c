/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:18:55 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/13 20:44:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	free_users(char ***user, char ***temp, char **temp_user)
{
	ft_strdel(&(**user));
	ft_strdel(temp_user);
	ft_strdel(&(**temp));
}

void	join_paths(char **user, char **temp, char **path, int opt)
{
	char	*temp_user;

	temp_user = ft_strdup(*user);
	ft_strdel(user);
	if (opt)
		*path = ft_strjoin("/Users/", &temp_user[1]);
	else
		*path = passwd_user(temp_user);
	if (!*path)
	{
		free_users(&user, &temp, &temp_user);
		return ;
	}
	if ((*temp))
		(*user) = ft_strjoin((*path), (*temp));
	else
		(*user) = ft_strdup((*path));
	ft_strdel(path);
	(*path) = ft_strdup((*user));
	free_users(&user, &temp, &temp_user);
}
