/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_window_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:22:37 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/10 21:29:16 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	init_window_size(t_term *term)
{
	struct winsize	w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) < 0)
	{
		ft_err_print(NULL, NULL, "could not get the terminal size", 2);
		exit(1);
	}
	term->ws_row = w.ws_row;
	term->ws_col = w.ws_col;
}
