/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_nl_mid_row.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:42:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 16:34:56 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It inserts a newline at the given row and position
 *
 * @param t pointer to the term structure
 * @param row The row number where the newline is to be added.
 * @param pos The position of the newline character in the input string.
 */
void	ft_add_nl_mid_row(t_term *t, ssize_t row, ssize_t pos)
{
	ssize_t	i;
	ssize_t	j;
	char	**new_arr;

	j = 0;
	i = -1;
	new_arr = (char **)ft_memalloc(sizeof(char *) * (size_t)(t->total_row + 2));
	while (++i <= t->total_row)
	{
		if (i == row)
			new_arr[i] = &t->inp[pos];
		else
			new_arr[i] = t->nl_addr[j++];
	}
	new_arr[i] = NULL;
	ft_memdel((void **)&t->nl_addr);
	t->nl_addr = new_arr;
}
