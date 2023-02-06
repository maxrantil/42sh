/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:09:07 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/06 14:38:22 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// static t_bg_jobs    *fg_parsing(t_bg_jobs *head, char *cmd)
// {
//     int         index;
//     t_bg_jobs   *ptr;

//     index = 0;
//     index = ft_atoi(cmd) - 1; // make a check for negative or and owerflow
//     ptr = head;
//     if (index >= 0)
//     {
//         while (ptr && index != ptr->index)
//             ptr = ptr->next;
//         if (ptr)
//             return (ptr);
//     }
// 	// if (!cmd || !ft_strcmp("%%", cmd) || !ft_strcmp("%+", cmd))
// 	// 	return (process_getpid(0, NULL, /* '+', */ head));
// 	// if (!ft_strcmp("%-", cmd))
// 	// 	return (process_getpid(0, NULL, /* '-', */ head));
// 	// if (*cmd == '%')
// 	// 	cmd++;
// 	// if (ft_isdigit(*cmd))
// 	// 	return (process_getpid(ft_atoi(cmd), /* NULL, */ 0, head));
// 	// else
// 	// 	return (process_getpid(0, cmd, /* 0, */ head));
// 	return (NULL);
// }

int	ft_fg(t_shell *sh, char **cmd)
{
    t_bg_jobs   *job;
	int		    status;

	job = bg_fetch_node(sh, *(cmd + 1));
	if (!job)
		ft_putstr("fg: no such job\n");
	else
	{
		if (job->status == DONE || job->status == TERMINATED)
		{
			display_job_node(sh, job);
			return (0);
		}
		display_pipeline_cmd(job);
		if (job->status == STOPPED || job->status == SUSPENDED)
			killpg(job->gpid, SIGCONT);
		if (ioctl(STDIN_FILENO, TIOCSPGRP, &job->gpid) == -1)
				exit (1); // this needs to be proper exit // error here
		transfer_to_fg(sh, job);
		job->status = RUNNING;
		waitpid(job->gpid, &status, WUNTRACED);
	}
	return (0);
}