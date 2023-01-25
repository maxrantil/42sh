/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:04:08 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/13 21:26:40 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It prints an error message to the specified file descriptor
 * 
 * @param file The file name that the error is about.
 * @param cmd The command that was run.
 * @param msg The error message to print.
 * @param fd the file descriptor to print to.
 * 
 * @return 1
 */
int	ft_err_print(char *file, char *cmd, char *msg, int fd)
{
	ft_putstr_fd(SHELL_NAME, fd);
	ft_putstr_fd(": ", fd);
	if (cmd)
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": ", fd);
	}
	if (file)
	{
		ft_putstr_fd(file, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
	return (1);
}
