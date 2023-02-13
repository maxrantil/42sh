/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passwd_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:30:21 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/13 15:36:29 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	free_strarr(char **strarr)
{
	int	i;

	i = 0;
	if (!strarr && !strarr[i])
		return ;
	while (strarr[i])
		ft_strdel(&strarr[i++]);
	free(strarr);
}

static char	**get_users(void)
{
	int		fd;
	char	*buf;
	int		rb;
	int		i;
	char	**users;

	fd = open("/etc/passwd", O_RDONLY);
	rb = 1;
	i = 0;
	users = (char **)ft_memalloc(sizeof(char *) * 1000);
	while (rb != 0)
	{
		rb = get_next_line(fd, &buf);
		if (rb == 0)
			break ;
		users[i++] = ft_strdup(buf);
		free(buf);
	}
	users[i] = NULL;
	close(fd);
	return (users);
}

static char	*get_uid(char *input)
{
	struct passwd	*passwd;
	char			*uid;

	passwd = getpwnam(input + 1);
	if (!passwd)
		return (NULL);
	uid = ft_itoa(passwd->pw_uid);
	return (uid);
}

static char	*get_user_path(char **users, char *uid)
{
	char	**info;
	char	*path;
	int		i;

	i = -1;
	info = NULL;
	path = NULL;
	while (users[++i])
	{
		info = ft_strsplit(users[i], ':');
		if (ft_strcmp(info[2], uid) == 0)
		{
			path = ft_strdup(info[5]);
			break ;
		}
		free_strarr(info);
	}
	free_strarr(info);
	return (path);
}

char	*passwd_user(char *input)
{
	char	*uid;
	char	**users;
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	users = get_users();
	uid = get_uid(input);
	if (!uid || !users)
	{
		free(uid);
		free_strarr(users);
		return (NULL);
	}
	while (users[i][0] == '#')
		i++;
	path = get_user_path(&users[i], uid);
	free(uid);
	free_strarr(users);
	return (path);
}
