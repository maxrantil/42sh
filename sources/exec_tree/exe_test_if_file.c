/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_test_if_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:45:22 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/24 13:08:29 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	check_directory_access(char *file)
{
	char	*tmp;

	tmp = ft_strdup(file);
	ft_strclr(ft_strrchr(tmp, '/'));
	if (access(tmp, F_OK) < 0)
	{
		ft_err_print(file, NULL, "No such file or directory", 2);
		ft_strdel(&tmp);
		return (0);
	}
	else if (access(tmp, W_OK) < 0)
	{
		ft_err_print(file, NULL, "Permission denied", 2);
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

int	test_if_file(char *file)
{
	struct stat	buf;

	if (stat(file, &buf) < 0)
	{
		if (ft_strchr(file, '/'))
			if (!check_directory_access(file))
				return (0);
		return (1);
	}
	if (buf.st_mode & S_IFDIR)
	{
		ft_err_print(file, NULL, "Is a directory", 2);
		return (0);
	}
	return (1);
}
