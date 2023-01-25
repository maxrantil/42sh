/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/25 15:03:20 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It handles backspaces and escape sequences
 *
 * @param t the t_term struct
 */
static void	ft_backspace_or_escape(t_term *t)
{
	if (t->ch == BACKSPACE && t->index)
		ft_backspace(t);
	if (t->ch == ESCAPE)
		ft_esc_parse(t);
}

/*
 * It inserts a character into the line, and if it's an enter, it checks if
 * the line is complete and if so, it ends the cycle
 *
 * @param t the structure containing all the information about the current line
 *
 * @return 1 or 0
 */
static int	ft_isprint_or_enter(t_term *t)
{
	ssize_t	delim_row;

	if ((ft_isprint(t->ch) || t->ch == ENTER) && t->bytes < (BUFF_SIZE - 1))
		ft_insertion(t);
	if (t->ch == ENTER)
	{
		delim_row = t->total_row;
		while (delim_row && !ft_is_prompt_line(t, delim_row))
			delim_row--;
		if ((!t->bslash && !(t->q_qty % 2) && !t->delim) \
			|| (t->delim && !ft_strcmp(t->nl_addr[delim_row], t->delim)))
		{
			ft_end_cycle(t);
			ft_setcursor(0, t->term_val[1] + t->total_row);
			return (1);
		}
		t->bslash = 0;
	}
	return (0);
}

static int	ctrl_d_exit(void)
{
	ft_printf("\n{RED}exit{RESET}");
	return (1);
}

/*
 * It reads input from the terminal, and if the input is a printable
 * character, it adds it to the current row, if the input is a backspace,
 * it deletes the last character from the current row, if the
 * input is an escape sequence, it calls the appropriate function,
 * and if the input is a control
 * character, it calls the appropriate function
 *
 * @param t the t_term struct
 */
int	ft_input_cycle(t_term *t)
{
	int		ctrl_d_ret;

	ft_add_nl_last_row(t, t->inp, 0);
	ft_printf("{GREEN}");
	t->c_col += write(1, PROMPT, (size_t)t->prompt_len);
	ft_printf("{RESET}");
	while (t->ch != -1)
	{
		t->ch = ft_get_input();
		if (ft_isprint_or_enter(t))
			return (0);
		if (t->ch == CTRL_D)
		{
			ctrl_d_ret = ctrl_d(t);
			if (ctrl_d_ret == 1)
				break ;
			if (ctrl_d_ret == -1)
				return (ctrl_d_exit());
		}
		ft_ctrl(t);
		ft_backspace_or_escape(t);
		if (t->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
	}
	return (0);
}
