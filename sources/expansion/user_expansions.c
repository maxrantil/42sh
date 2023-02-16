/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:24:20 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/14 15:44:27 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*init_user_exp(char *str, char **temp, char **user)
{
	(*temp) = NULL;
	(*user) = NULL;
	if (!str[1] || str[1] == '/')
		return (NULL);
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

static char	*get_uid(char *input)
{
	struct passwd	*passwd;

	passwd = getpwnam(input);
	if (!passwd)
		return (NULL);
	return (ft_strdup(passwd->pw_dir));
}

char	*user_expansions(char *input)
{
	char	*uid;
	char	*user;
	char	*path;
	char	*temp;

	path = NULL;
	if (!init_user_exp(input, &temp, &user))
		return (NULL);
	uid = get_uid(&user[1]);
	if (!uid)
	{
		ft_strdel(&temp);
		return (NULL);
	}
	path = ft_strjoin(uid, temp);
	ft_strdel(&temp);
	ft_strdel(&uid);
	ft_strdel(&user);
	return (path);
}
