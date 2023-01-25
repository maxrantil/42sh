/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_reset_nl.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:29:50 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/12 16:00:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It resets the newline addresses of the history buffer
 * 
 * @param t the term struct
 * @param inp the string to be printed
 */
void	ft_history_reset_nl(t_term *t)
{
	ssize_t	i;
	ssize_t	col;
	ssize_t	prompt_len;

	i = -1;
	col = 0;
	t->total_row = 0;
	ft_memdel((void **)&t->nl_addr);
	ft_add_nl_last_row(t, t->inp, 0);
	while (t->inp[++i])
	{
		col++;
		prompt_len = ft_get_prompt_len(t, t->total_row);
		if (!t->total_row)
			prompt_len += t->term_val[0];
		if ((col + prompt_len) == t->ws_col || t->inp[i] == '\n')
		{
			col = 0;
			t->total_row++;
			ft_add_nl_last_row(t, t->inp, i + 1);
		}
	}
	t->bytes = &t->inp[i] - t->nl_addr[0];
	t->index = t->bytes;
}
