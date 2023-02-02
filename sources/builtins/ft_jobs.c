/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:54 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/02 11:18:32 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// int	ft_jobs(t_shell *sh)
// {
// 	t_bg_jobs *job;
// 	pid_t	*tmp;
// 	char	***ptr;
// 	char	**dbl;

// 	job = sh->bg_node;
// 	while (job)
// 	{
// 		ft_printf("index %d\n", job->index);
// 		ft_printf("status %d\n", job->status);
// 		ft_printf("gpid %d\n", job->gpid);
// 		tmp = job->pid;
// 		while (tmp && *tmp)
// 			ft_printf("pid: %d\n", *(tmp++));
// 		ptr = job->cmd;
// 		while (ptr && *ptr)
// 		{
// 			dbl = *ptr;
// 			while (*dbl)
// 			{
// 				ft_printf("cmd: %s\n", *dbl);
// 				dbl++;
// 			}
// 			ptr++;
// 		}
// 		job = job->next;
// 	}	
// 	return (0);
// }

int	ft_jobs(t_shell *sh)
{
	t_bg_jobs *job;

	job = sh->bg_node;
	while (job)
	{
		// ft_printf("gpid %d| ", job->gpid);
        display_process_node(job);
		job = job->next;
	}	
	return (0);
}
