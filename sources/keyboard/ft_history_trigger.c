/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_trigger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:59:10 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/12 16:07:28 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It copies the current input into a buffer, pushes the current input into
 * the history ft_vector, and sets the current row to the history row
 * 
 * @param t the term structure
 */
static void	ft_history_push(t_term *t, ssize_t row)
{
	if (t->history_row == -1)
	{
		t->input_cpy = ft_strsub(t->nl_addr[row], 0, \
		ft_strlen(t->nl_addr[row]));
		if (*t->history_buff)
		{
			ft_nl_removal(t);
			ft_history_add_command(t, t->history_buff);
			ft_memset((void *)t->history_buff, '\0', \
			ft_strlen(t->history_buff));
		}
		t->history_row = row;
	}
	t->c_row = t->history_row;
}

/**
 * It copies the contents of the history buffer into the input buffer
 * 
 * @param t the term structure
 * @param dst the buffer that will be written to
 * @param src the string to be copied
 */
static void	ft_historycpy(t_term *t, char *dst, char *src)
{
	int	i;
	int	len;

	i = -1;
	len = (int)ft_strlen(t->inp);
	while (src[++i] && (len + i) < (BUFF_SIZE - 1))
		dst[i] = src[i];
}

/**
 * It updates the current
 * input line with the history line
 * 
 * @param t the term structure
 * @param history the history string to be copied into the input line
 */
static void	ft_history_inp_update(t_term *t, char *history, ssize_t row)
{
	ft_strclr(t->nl_addr[row]);
	if (history)
		ft_historycpy(t, t->nl_addr[row], history);
	else if (t->input_cpy)
		ft_historycpy(t, t->nl_addr[row], t->input_cpy);
}

/**
 * It clears the line from the cursor to the end of the screen
 * 
 * @param t the term structure
 * @param row the row number of the line to be cleared
 */
static void	ft_history_clear_line(t_term *t)
{
	if (!t->history_row)
		ft_setcursor(t->term_val[0], (t->term_val[1] + t->history_row));
	else
		ft_setcursor(0, (t->term_val[1] + t->history_row));
	ft_run_capability("cd");
}

/**
 * It takes the current input, pushes it to the history, then replaces
 * the current input with the history entry
 * 
 * @param t The terminal structure
 * @param his The history number to be retrieved.
 * 
 * @return the address of the first element of the array.
 */
void	ft_history_trigger(t_term *t, ssize_t his)
{
	ssize_t	row;
	char	*history;

	history = NULL;
	if (t->c_row != t->total_row)
		return ;
	row = ft_history_trigger_row(t);
	ft_history_push(t, row);
	ft_run_capability("vi");
	if (t->history_arr[t->history_size - (unsigned long)his])
		history = t->history_arr[t->history_size - (size_t)his];
	ft_history_clear_line(t);
	ft_history_inp_update(t, history, row);
	ft_history_reset_nl(t);
	ft_quote_flag_reset(t);
	if (t->term_val[1] + t->total_row >= t->ws_row)
		t->term_val[1] = t->ws_row - (t->total_row + 1);
	ft_print_input(t, t->c_row, 1);
	if (!history)
	{
		ft_strdel(&t->input_cpy);
		t->history_row = -1;
	}
	ft_run_capability("ve");
}
