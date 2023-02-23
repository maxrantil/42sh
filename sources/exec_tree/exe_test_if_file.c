/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_test_if_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:45:22 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/23 13:45:56 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	test_if_file(char *file)
{
	struct stat	buf;

	if (stat(file, &buf) < 0)
	{
		if (ft_strchr(file, '/'))
		{
			ft_err_print(file, NULL, "No such file or directory", 2);
			return (0);
		}
		return (1);
	}
	if (buf.st_mode & S_IFDIR)
	{
		ft_err_print(file, NULL, "Is a direcotry", 2);
		return (0);
	}
	return (1);
}
