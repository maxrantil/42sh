/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_history_reset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:11:57 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/26 11:32:37 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_search_history_reset(t_term *t)
{
	ft_run_capability("cl");
	t->term_val[0] = 0;
	t->term_val[1] = 0;
	ft_print_input(t, 0, 0);
	ft_memdel((void **)&t->config->ptr);
	init_search_history_config(t, t->config);
	init_interface(t, t->config);
	history_options(t, t->config);
	ft_display_to_show(t->config);
	ft_display_input(t, t->config);
	ft_setcursor(0, t->config->row);
	print_selector("RED");
	t->config->cursor = t->config->row;
	t->config->index = t->config->index_max;
	ft_setcursor(t->config->input_cur_col, t->config->input_term_row);
}

void	ft_display_input(t_term *t, t_search_history *config)
{
	ft_setcursor(0, config->input_term_row);
	print_selector("BLUE");
	ft_run_capability("nd");
	config->input_cur_col = 2;
	config->input_cur_col += write(1, t->nl_addr[t->total_row], \
	ft_strlen(t->nl_addr[t->total_row]));
}

void	ft_display_to_show(t_search_history *config)
{
	ft_setcursor(0, config->match_term_row);
	ft_run_capability("ce");
	ft_printf("{CYAN}%2s%d/%d %cS{RESET}", "", config->match, \
	config->max_to_show, '+');
}
