/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:23:30 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/06 13:00:16 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It exits the shell
 * 
 * @param sesh The session struct.
 * @param status The exit status of the shell.
 */
void	ft_exit(t_session *sesh, int status)
{
	sesh->exit_stat = status;
	ft_printf("{RED}exit{RESET}\n");
	ft_history_write_to_file(sesh->term);
	ft_raw_disable(sesh->orig_termios);
	if (sesh->term->clipboard.buff)
		ft_strdel(&sesh->term->clipboard.buff);
	shell_end_cycle(sesh);
	exit(status);
}
