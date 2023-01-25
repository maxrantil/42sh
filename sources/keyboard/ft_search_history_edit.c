/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_history_edit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:24:07 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/25 13:33:40 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void edit_mode(bool bs, t_term *t, t_search_history *config)
{
    if (bs)
	{
		ft_deletion_shift(t, --t->index);
		--config->input_cur_col;
	}
	else
	{
		t->inp[t->index++] = config->inp;
		++t->bytes;
		++config->input_cur_col;
	}
}

static void update_var_and_interface(t_term *t, t_search_history *config)
{
    config->history_index = t->history_size - 1;
	config->match = count_matches(t, config);
	config->to_show = config->match - 1;
	history_options(t, config);
	config->index = config->index_max;
	ft_display_to_show(config);
	ft_display_input(t, config);
    if (config->to_show)
	{
		ft_setcursor(0, config->row);
		print_selector("RED");
	}
	ft_setcursor(config->input_cur_col, config->input_term_row);
}

void	edit_input(t_term *t, t_search_history *config)
{
	bool	bs;

	bs = false;
	if (config->inp == BACKSPACE \
	&& &t->inp[t->index] > t->nl_addr[t->total_row])
		bs = true;
	if (!ft_isprint(config->inp) && !bs)
		return ;
	if (ft_isprint(config->inp) && config->input_cur_col == (t->ws_col - 2))
		return ;
	ft_run_capability("vi");
	config->cursor = config->row;
	ft_setcursor(1, config->row);
	ft_run_capability("cb");
    edit_mode(bs, t, config);
    update_var_and_interface(t, config);
	if (bs)
		ft_run_capability("ce");
	ft_run_capability("ve");
}
