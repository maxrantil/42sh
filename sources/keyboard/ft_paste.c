/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:04:10 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/13 11:54:07 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	paste_into_array(t_term *t)
{
	int	i;

	i = -1;
	while (t->bytes < (BUFF_SIZE - 1) && t->clipboard.buff[++i])
	{
		t->c_col++;
		ft_putc(t->clipboard.buff[i]);
		ft_shift_nl_addr(t, 1);
		if (t->inp[t->index])
			ft_shift_insert(t);
		t->inp[t->index++] = t->clipboard.buff[i];
		t->bytes++;
		ft_trigger_nl(t);
		if (t->c_col == t->ws_col)
			t->c_row++;
	}
}

/*
 * It pastes the contents of the clipboard into the input buffer
 *
 * @param t The term structure.
 */
void	ft_paste(t_term *t)
{
	if (t->clipboard.buff)
	{
		ft_run_capability("vi");
		paste_into_array(t);
		if (t->inp[t->index])
			ft_print_trail(t);
		if (t->clipboard.type == CUT)
			ft_strdel(&t->clipboard.buff);
		ft_quote_flag_reset(t);
		if (t->heredoc)
			ft_delim_fetch(t);
		ft_run_capability("ve");
	}
}
