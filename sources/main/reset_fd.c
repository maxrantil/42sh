/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:31:23 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/26 09:55:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	reset_fd(char *terminal)
{
	int		fd;

	close (STDIN_FILENO);
	open(terminal, O_RDWR);
	close (STDOUT_FILENO);
	open(terminal, O_RDWR);
	close (STDERR_FILENO);
	open(terminal, O_RDWR);
	fd = SH_FD_MAX;
	while (fd >= 3)
	{
		close(fd);
		--fd;
	}
}
