/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:23:30 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/25 19:17:29 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	get_exit_status(char **commands)
{
	int		status;

	if (!commands[1])
		return (0);
	status = ft_atoi(commands[1]);
	if (strlen(commands[1]) > 12 && commands[1][0] != '-' && status < 1)
	{
		write(2, "42sh: exit: value bigger than max int, exiting with 1\n", 54);
		return (1);
	}
	if (status == 0)
	{
		ft_printf("42sh: exit: %s: numeric argument required\n", commands[1]);
		return (2);
	}
	if (status > 255)
		return (status % 256);
	if (status < 0)
	{
		status = (status * -1) % 256;
		return (256 - status);
	}
	return (status);
}

/**
 * It exits the shell
 * 
 * @param sesh The session struct.
 * @param status The exit status of the shell.
 */
int	ft_exit(t_session *sesh, char **commands)
{
	ft_printf("{RED}exit{RESET}\n");
	if (commands[1] && commands[2])
	{
		write(2, "42sh: exit: too many arguments\n", 32);
		sesh->exit_stat = 1;
		return (0);
	}
	else if (commands[1])
	{	
		sesh->exit_stat = get_exit_status(commands);
		ft_history_write_to_file(sesh->term);
		ft_raw_disable(sesh->orig_termios);
		if (sesh->term->clipboard.buff)
			ft_strdel(&sesh->term->clipboard.buff);
		shell_end_cycle(sesh);
	}
	exit(sesh->exit_stat);
}
