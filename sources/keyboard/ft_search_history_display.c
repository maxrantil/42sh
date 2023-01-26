/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_history_display.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:45:11 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/26 11:31:13 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	history_option_display(t_term *t, char **his_arr, \
int his_index)
{
	int	i;
	int	col;

	i = -1;
	col = 10;
	ft_printf("%2s%-5d%2s", "", his_index, "");
	while (his_arr[his_index][++i])
	{
		if (his_arr[his_index][i] != '\n')
			ft_putchar(his_arr[his_index][i]);
		else
		{
			ft_putstr("\\n");
			col++;
		}
		col++;
		if (col == t->ws_col - 3)
		{
			ft_putstr("..");
			break ;
		}
	}
}

static int	init_var_cpy(int *row, int *to_show, int *display_row, \
t_search_history *config)
{
	*display_row = config->row;
	*row = config->history_rows;
	*to_show = config->to_show + config->history_rows;
	ft_run_capability("vi");
	return (config->history_index);
}

static void	clear_excess_lines(int row, int display, t_search_history *config)
{
	config->index_max = (config->history_rows - row) - 1;
	while (row-- > 0)
	{
		ft_setcursor(0, display--);
		ft_run_capability("ce");
	}
	ft_run_capability("ve");
}

void	history_options(t_term *t, t_search_history *config)
{
	int	row;
	int	index;
	int	to_show;
	int	dis_row;
	int	his_index;

	index = 0;
	his_index = init_var_cpy(&row, &to_show, &dis_row, config);
	while (row && his_index && t->history_arr[his_index] \
		&& to_show && index < config->match)
	{
		if (ft_is_match(t->history_arr[his_index], \
		t->nl_addr[t->total_row]))
		{
			ft_setcursor(0, dis_row);
			ft_run_capability("ce");
			history_option_display(t, t->history_arr, his_index);
			dis_row--;
			row--;
			config->ptr[index++] = his_index;
			to_show--;
		}
		his_index--;
	}
	clear_excess_lines(row, dis_row, config);
}
