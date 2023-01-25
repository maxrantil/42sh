/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_test_if_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:45:22 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/19 16:16:32 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	test_if_file(char *file)
{
	struct stat	buf;

	if (stat(file, &buf) < 0)
		return (1);
	if (buf.st_mode & S_IFDIR)
	{
		ft_err_print(file, NULL, "Is a direcotry", 2);
		return (0);
	}
	return (1);
}
