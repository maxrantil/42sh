/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restart_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:56:42 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/14 09:13:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	heredoc_reset(t_term *t)
{
	if (t->delim)
	{
		ft_memcpy(t->history_buff, t->inp, (unsigned long)t->bytes);
		ft_nl_removal(t);
		ft_history_add_command(t, t->history_buff);
		ft_strdel(&t->delim);
	}
	t->heredoc = 0;
}

static void	reset_values(t_term *t)
{
	t->ch = 0;
	t->his = 0;
	t->c_col = 0;
	t->quote = 0;
	t->q_qty = 0;
	t->bytes = 0;
	t->index = 0;
	t->bslash = 0;
	t->total_row = 0;
	t->history_row = -1;
	t->c_row = t->total_row;
}

/*
 * It resets the terminal
 * to its initial state
 *
 * @param t the term structure
 */

void	ft_restart_cycle(t_term *t)
{
	if (t->term_val[1] + t->total_row + 1 == t->ws_row)
	{
		ft_setcursor(0, t->ws_row);
		ft_run_capability("sf");
	}
	else
		ft_setcursor(0, (t->term_val[1] + t->total_row) + 1);
	heredoc_reset(t);
	reset_values(t);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
	ft_memdel((void **)&t->nl_addr);
	ft_add_nl_last_row(t, t->inp, 0);
	ft_strclr(t->inp);
	ft_strclr(t->history_buff);
	ft_printf("{GREEN}");
	get_term_val(t->term_val);
	write(1, PROMPT, (size_t)t->prompt_len);
	ft_printf("{RESET}");
}
