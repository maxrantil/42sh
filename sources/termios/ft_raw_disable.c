/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raw_disable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:43:24 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/10 19:04:45 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It disables raw mode by setting the terminal attributes to the original
 * terminal attributes
 *
 * @param orig_termios The original terminal attributes.
 */
void	ft_raw_disable(struct termios orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
