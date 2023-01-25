/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_history_move.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:15:26 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/25 13:17:28 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	get_next_index(t_term *t, t_search_history *config)
{
	if ((size_t)config->history_index < (t->history_size - 1))
	{
		config->history_index++;
		if (*t->nl_addr[t->total_row])
		{
			while ((size_t)config->history_index < (t->history_size - 1) \
			&& !ft_strstr(t->history_arr[config->history_index], \
			t->nl_addr[t->total_row]))
				config->history_index++;
		}
	}	
}

void	ft_selector_do(t_term *t, t_search_history *config)
{
	ft_setcursor(0, config->cursor);
	if (config->index < config->index_max)
	{
		++config->cursor;
		++config->index;
		++config->to_show;
		ft_run_capability("cb");
	}
	else if ((size_t)config->history_index < (t->history_size - 1))
	{
		++config->to_show;
		config->history_index = config->ptr[0];
		get_next_index(t, config);
		history_options(t, config);
	}
	ft_setcursor(0, config->cursor);
	print_selector("RED");
	ft_setcursor(config->input_cur_col, config->input_term_row);
}

void	ft_selector_up(t_term *t, t_search_history *config)
{
	ft_setcursor(0, config->cursor);
	if (config->index > 0)
	{
		--config->cursor;
		--config->index;
		--config->to_show;
		ft_run_capability("cb");
	}
	else if (config->index_max == (config->history_rows - 1) \
	&& config->ptr[config->index_max - (config->index)] > 1)
	{
		--config->to_show;
		config->history_index = config->ptr[1];
		history_options(t, config);
	}
	ft_setcursor(0, config->cursor);
	print_selector("RED");
	ft_setcursor(config->input_cur_col, config->input_term_row);
}
