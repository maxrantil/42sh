/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raw_enable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:41:48 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/31 12:26:31 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It puts the terminal into raw mode
 *
 * @return The original terminal settings.
 */
void	ft_raw_enable(t_shell *sh)
{
	struct termios	raw_termios;

	if (tcgetattr(STDIN_FILENO, &sh->orig_termios) == -1)
	{
		write(2, "error tcgetattr\n", 16);
		exit(1);
	}
	raw_termios = sh->orig_termios;
	raw_termios.c_lflag &= ~(ICANON | ECHO);
	raw_termios.c_iflag &= ~(IXON | BRKINT);
	raw_termios.c_cc[VMIN] = 0;
	raw_termios.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios) == -1)
	{
		write(2, "error tcsetattr\n", 16);
		exit(1);
	}
}
