/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raw_enable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:41:48 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/24 15:11:11 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It puts the terminal into raw mode
 *
 * @return The original terminal settings.
 */
struct termios	ft_raw_enable(void)
{
	struct termios	orig_termios;
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
	{
		write(2, "error tcgetattr\n", 16);
		exit(1);
	}
	raw = orig_termios;
	raw.c_lflag &= ~(ICANON | ECHO);
	raw.c_iflag &= ~(IXON | BRKINT);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	{
		write(2, "error tcsetattr\n", 16);
		exit(1);
	}
	return (orig_termios);
}
