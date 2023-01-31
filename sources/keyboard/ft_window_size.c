/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:25:07 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/31 12:48:12 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "keyboard.h"
#include "ft_42sh.h"

extern t_shell	*g_sh;

static void	reset_screen(t_term *t)
{
	t->term_val[0] = 0;
	t->term_val[1] = 0;
	ft_run_capability("cl");
	ft_reset_nl_addr(t);
	ft_print_input(t, 0, 0);
	set_new_cur_pos(t);
}

/*
 * It resets the cursor position and prints the trail of the input string
 *
 * @param t the term structure
 */
void	ft_window_size(t_term *t)
{
	struct winsize	size;

	ft_run_capability("vi");
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0)
	{
		ft_putstr_fd("could not get the terminal size", 2);
		ft_raw_disable(g_sh->orig_termios);
		exit(1);
	}
	t->ws_col = size.ws_col;
	t->ws_row = size.ws_row;
	if (*t->inp)
		reset_screen(t);
	else
	{
		get_term_val(t->term_val);
		t->c_col = t->term_val[0];
		t->term_val[0] -= t->prompt_len;
	}
	ft_run_capability("ve");
}
