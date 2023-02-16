/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:16:30 by spuustin          #+#    #+#             */
/*   Updated: 2023/02/16 17:30:41 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	long_exit_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_printf("42sh: exit: %s: numeric argument required\n", str);
			return (2);
		}
		i++;
	}
	write(2, "42sh: exit: exit status longer than long long", 46);
	write(2, ", exiting with 1\n", 18);
	return (1);
}

static int	get_exit_status(char **commands)
{
	int		status;

	if (!commands[1])
		return (0);
	status = ft_atoi(commands[1]);
	if (status == 0 || ft_strlen(commands[1]) > 18)
	{
		ft_printf("42sh: exit: %s: numeric argument required\n", commands[1]);
		return (2);
	}
	if (status == -1)
		return (long_exit_string(commands[1]));
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
 * @param sh The session struct.
 * @param status The exit status of the shell.
 */
int	ft_exit(t_shell *sh, char **commands)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	jobs_exit_check(sh);
	if (sh->exit_confirm == -1)
	{
		if (commands[0] && commands[1] && commands[2])
		{
			write(2, "42sh: exit: too many arguments\n", 32);
			sh->exit_stat = 1;
			return (0);
		}
		else if (commands[0])
		{
			sh->exit_stat = get_exit_status(commands);
			ft_history_write_to_file(sh->term);
			ft_raw_disable(sh->orig_termios);
			if (sh->term->clipboard.buff)
				ft_strdel(&sh->term->clipboard.buff);
			shell_end_cycle(sh);
		}
		exit(sh->exit_stat);
	}
	else
		ft_putstr("There are stopped jobs.\n");
	return (0);
}
