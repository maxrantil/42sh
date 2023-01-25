/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_history_init.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:48:59 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/25 13:49:47 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	init_index_ptr(t_search_history *config)
{
	int	i;

	i = -1;
	config->ptr = (int *)ft_memalloc(sizeof(int) * (config->history_rows));
	while (++i < config->history_rows)
		config->ptr[i] = -1;
}

void	init_search_history_config(t_term *t, t_search_history *config)
{
	config->status = 1;
	config->match = 0;
	config->history_rows = 10;
	init_index_ptr(config);
	config->max_to_show = 50;
	if (t->history_size < (size_t)config->max_to_show)
		config->max_to_show = t->history_size - 1;
	config->to_show = config->max_to_show - 1;
	config->history_index = t->history_size - 1;
	config->start_cur_row = t->term_val[1] + t->total_row;
	config->match = count_matches(t, config);
	config->row = config->start_cur_row + (config->history_rows - 1);
	config->match_term_row = config->row + 1;
	config->input_term_row = config->row + 2;
}

void	init_interface(t_term *t, t_search_history *config)
{
	int	diff;

	ft_run_capability("cb");
	ft_run_capability("cd");
	diff = config->input_term_row - t->ws_row;
	if (diff >= 0)
	{
		ft_run_capability("sc");
		config->start_cur_row -= diff + 1;
		t->term_val[1] -= diff + 1;
		while (diff-- >= 0)
		{
			ft_setcursor(0, t->ws_row);
			ft_run_capability("sf");
		}
		config->row = t->ws_row - 3;
		config->match_term_row = config->row + 1;
		config->input_term_row = config->row + 2;
		ft_run_capability("rc");
	}
}
