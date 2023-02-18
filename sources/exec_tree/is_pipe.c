/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:42:15 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/18 09:30:53 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	is_pipe(t_shell *sh, int fd)
{
	if (sh->pipe->piping && (fd == sh->pipe->write_pipe[1]
			|| fd == sh->pipe->write_pipe[0] || fd == sh->pipe->read_pipe[0]
			|| fd == sh->pipe->read_pipe[1]))
		return (1);
	return (0);
}
