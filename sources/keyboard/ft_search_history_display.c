/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_history_display.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:45:11 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/25 13:18:41 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

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

static void history_option_display(t_term *t, char *str)
{
	int	col;

	col = 10;
    while (*str)
    {
        if (*str != '\n')
            ft_putchar(*str);
        else
		{
            ft_putstr("\\n");
			col++;
		}
        str++;
		col++;
		if (col == t->ws_col - 3)
		{
			ft_putstr("..");
			break ;
		}
	}
}

void	history_options(t_term *t, t_search_history *config)
{
	int	index;
	int	row_cpy;
	int	to_show_cpy;
	int	display_row_cpy;
	int	history_index_cpy;

	ft_run_capability("vi");
	index = 0;
	display_row_cpy =  config->row;
	row_cpy = config->history_rows;
	history_index_cpy = config->history_index;
	to_show_cpy = config->to_show + config->history_rows;
	while (row_cpy && history_index_cpy && t->history_arr[history_index_cpy] && to_show_cpy && index < config->match)
	{
		if (ft_is_match(t->history_arr[history_index_cpy], t->nl_addr[t->total_row])) // This logic needs to be improved
		{
			ft_setcursor(0, display_row_cpy);
			ft_run_capability("ce");
			ft_printf("%2s%-5d%2s", "", history_index_cpy, "");
            history_option_display(t, t->history_arr[history_index_cpy]);
			display_row_cpy--;
			row_cpy--;
			config->ptr[index++] = history_index_cpy;
			to_show_cpy--;
		}
		history_index_cpy--;
	}
	config->index_max = (config->history_rows - row_cpy) - 1;
	while (row_cpy-- > 0)
	{
		ft_setcursor(0, display_row_cpy--);
		ft_run_capability("ce");
	}
	ft_run_capability("ve");
}
