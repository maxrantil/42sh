/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:33:02 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/25 15:41:59 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It prints the arguments
 * passed to it, separated by spaces, and optionally followed by a newline
 *
 * @param cmd The command line arguments.
 * @param nl_flag if true, don't print a newline at the end of the output
 */
static void	echo_print(char **cmd, int offset, int flag)
{
	int		i;

	i = 1;
	while (cmd[i + offset])
	{
		if (cmd[i + offset])
			ft_putstr(cmd[i + offset]);
		i++;
		if (cmd[i + offset])
			ft_putstr(" ");
	}
	if (flag == 0)
		ft_putstr("\n");
}

/**
 * It checks if the file descriptor 1 (stdout) is valid
 *
 * @return The return value of the function.
 */
static int	echo_fd_check(void)
{
	struct stat	buf;

	if (fstat(1, &buf) == -1)
	{
		ft_err_print(NULL, "echo", "write error: Bad file descriptor", 2);
		return (1);
	}
	return (0);
}

/**
 * It prints the arguments to the standard output, with a newline at the end,
 * unless the first argument is "-n", in which case it doesn't print the newline
 *
 * @param cmd The command line arguments.
 *
 * @return The return value of the function.
 */
int	ft_echo(t_shell *sh, char **cmd)
{
	sh->exit_stat = 0;
	if (echo_fd_check())
	{
		sh->exit_stat = 1;
		return (0);
	}
	if (!(*cmd))
		ft_putstr("\n");
	else
	{
		echo_print(cmd, check_flag(sh, cmd, 'n'), sh->is_flag_on);
		sh->is_flag_on = 0;
	}
	return (0);
}
