/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wtermsig_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:48:24 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/23 10:28:27 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	job_wtermsig_msg_continue(int status)
{
	if (status == SIGSEGV)
		ft_printf("Segmentation fault: %d\n", status);
	else if (status == SIGSYS)
		ft_printf("Bad system call: %d\n", status);
	else if (status == SIGALRM)
		ft_printf("Alarm clock: %d\n", status);
	else if (status == SIGTERM)
		ft_printf("Terminated: %d\n", status);
	else if (status == SIGXCPU)
		ft_printf("CPU time limit exceeded: %d\n", status);
	else if (status == SIGVTALRM)
		ft_printf("Virtual timer expired: %d\n", status);
	else if (status == SIGPROF)
		ft_printf("Profiling timer expired: %d\n", status);
	else if (status == SIGUSR1)
		ft_printf("User defined signal 1: %d\n", status);
	else if (status == SIGUSR2)
		ft_printf("User defined signal 2: %d\n", status);
}

void	job_wtermsig_msg(int status)
{
	if (status == SIGHUP)
		ft_printf("Hangup: %d\n", status);
	else if (status == SIGQUIT)
		ft_printf("Quit: %d\n", status);
	else if (status == SIGILL)
		ft_printf("Illegal instruction: %d\n", status);
	else if (status == SIGTRAP)
		ft_printf("Trace/BPT trap: %d\n", status);
	else if (status == SIGABRT)
		ft_printf("Abort trap: %d\n", status);
	else if (status == SIGEMT)
		ft_printf("EMT trap: %d\n", status);
	else if (status == SIGFPE)
		ft_printf("Floating point exception: %d\n", status);
	else if (status == SIGKILL)
		ft_printf("Killed: %d\n", status);
	else if (status == SIGBUS)
		ft_printf("Bus error: %d\n", status);
	job_wtermsig_msg_continue(status);
}
