/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_write_to_file.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:59:21 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/13 11:08:10 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * It writes the history to the file
 *
 * @param t The terminal structure.
 */
void	ft_history_write_to_file(t_term *t)
{
	int		fd;
	size_t	cpy;

	fd = open(t->history_file, O_WRONLY | O_TRUNC);
	if (fd)
	{
		cpy = 0;
		while (cpy < t->history_size)
		{
			ft_putendl_fd((char *)t->history_arr[cpy], fd);
			cpy++;
		}
		close(fd);
	}
}
