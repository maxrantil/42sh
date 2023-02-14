/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_wrap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:28:53 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/14 15:29:25 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

/**
 * It forks, and if it fails, it exits
 * 
 * @return The pid of the child process.
 */
int	fork_wrap(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit_error(g_sh, 1, "ERROR: fork failed");
	return (pid);
}
