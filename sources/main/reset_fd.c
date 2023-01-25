/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:31:23 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/15 14:45:08 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
