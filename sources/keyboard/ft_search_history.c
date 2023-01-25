/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:36:20 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/25 13:58:48 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	return_to_shell(t_term *t, t_search_history *config)
{
	if (!t->total_row)
		t->c_col = t->prompt_len;
	else
		t->c_col = t->m_prompt_len;
	t->c_col += ft_strlen(t->nl_addr[t->total_row]);
	ft_setcursor(0, config->start_cur_row);
	ft_history_reset_nl(t);
	ft_quote_flag_reset(t);
	ft_run_capability("cd");
	ft_print_input(t, t->c_row, 0);
	config->status = 0;
}

static void	start_interface(t_term *t, t_search_history *config)
{
	ft_run_capability("vi");
	init_search_history_config(t, config);
	init_interface(t, config);
	history_options(t, config);
	ft_display_to_show(config);
	ft_display_input(t, config);
	ft_setcursor(0, config->row);
	print_selector("RED");
	config->cursor = config->row;
	config->index = config->index_max;
	ft_setcursor(config->input_cur_col, config->input_term_row);
	ft_run_capability("ve");
}

static void	up_and_down(t_term *t, t_search_history *config)
{
	ft_run_capability("vi");
	config->inp = ft_get_input();
	if (config->inp == 65 && config->to_show)
		ft_selector_up(t, config);
	else if (config->inp == 66 && config->to_show < config->max_to_show)
		ft_selector_do(t, config);
	ft_run_capability("ve");
}

void	ft_search_history(t_term *t)
{
	t_search_history	config;

	t->config = &config;
	signal(SIGINT, search_history_sigs);
	signal(SIGWINCH, search_history_sigs);
	start_interface(t, &config);
	while (config.status)
	{
		config.inp = ft_get_input();
		if (config.inp == 91)
			up_and_down(t, &config);
		else if (config.inp == '\n')
			ft_select_history(t, &config);
		else if ((ft_isprint(config.inp) || config.inp == BACKSPACE))
			edit_input(t, &config);
		else if (config.inp == 18)
			return_to_shell(t, &config);
	}
	ft_memdel((void **)&config.ptr);
	t->config = NULL;
	signal(SIGINT, sig_session_handler);
	signal(SIGWINCH, sig_session_handler);
}
