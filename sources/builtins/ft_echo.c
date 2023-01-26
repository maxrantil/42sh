/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:33:02 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/26 09:56:21 by mrantil          ###   ########.fr       */
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
static void	echo_print(char **cmd, bool nl_flag)
{
	while (*cmd)
	{
		if (*cmd)
			ft_putstr(*cmd);
		cmd++;
		if (*cmd)
			ft_putstr(" ");
	}
	if (!nl_flag)
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
	bool	nl_flag;

	sh->exit_stat = 0;
	if (echo_fd_check())
	{
		sh->exit_stat = 1;
		return (0);
	}
	nl_flag = false;
	if (!(*cmd))
		ft_putstr("\n");
	else
	{
		if (!ft_strcmp(*(cmd++), "-n"))
			nl_flag = true;
		echo_print(cmd, nl_flag);
	}
	return (0);
}
