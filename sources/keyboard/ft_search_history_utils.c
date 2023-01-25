/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_seash_history_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:46:54 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/21 12:18:5 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	print_selector(char *color)
{	
	if (!ft_strcmp("RED", color))
		ft_printf("{RED}>{RESET}");
	if (!ft_strcmp("BLUE", color))
		ft_printf("{BLUE}>{RESET}");
}

bool	ft_is_match(char *haystack, char *needle)
{
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(needle);
	while (*haystack && needle[x])
	{
		if (*haystack == needle[x])
			++x;
		haystack++;
	}
	if (x == len)
		return (1);
	else
		return (0);
}

int	count_matches(t_term *t, t_search_history *config)
{
	int	i;
	int	count;
	int	to_show;

	count = 0;
	to_show = 0;
	i = config->history_index;
	if (*t->nl_addr[t->total_row] == '\0')
		return (config->max_to_show);
	while (i && to_show < config->max_to_show)
	{
		if (ft_is_match(t->history_arr[i], t->nl_addr[t->total_row]))
		{
			count++;
			to_show++;
		}
		i--;
	}
	return (count);
}

void	ft_select_history(t_term *t, t_search_history *config)
{
	if (config->index >= 0 && config->index >= 0)
	{
		t->c_col = ft_strlen(t->history_arr \
		[config->ptr[config->index_max - config->index]]);
		t->bytes -= ft_strlen(t->nl_addr[t->total_row]);
		ft_memcpy(t->nl_addr[t->total_row], t->history_arr \
		[config->ptr[config->index_max - config->index]], t->c_col);
		t->bytes += t->c_col;
		t->index = t->bytes;
	}
	if (!t->total_row)
		t->c_col += t->prompt_len;
	else
		t->c_col += t->m_prompt_len;
	ft_setcursor(0, config->start_cur_row);
	ft_run_capability("cd");
	ft_history_reset_nl(t);
	ft_quote_flag_reset(t);
	ft_print_input(t, t->c_row, 0);
	t->c_row = t->total_row;
	config->status = 0;
}
