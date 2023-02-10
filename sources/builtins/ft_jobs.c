/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:54 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/10 18:17:57 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	validate_options(t_shell *session, char **commands)
{
	int		i;

	i = 1;
	while(commands[i])
	{
		if (ft_strequ(commands[i], "--"))
		{
			i++;
			break;
		}
		if (str_only_contains_chars(commands[i], "lp") == 0)
		{
			//print usage here
			return (0);
		}
		if (commands[i][0] != '-' || !str_only_contains_chars(commands[i], "lp"))
			break;
		session->option = commands[i][ft_strlen(commands[i]) - 1];
		i++;
	}
	session->option_count = i - 1;
	return (1);
}

int	ft_jobs(t_shell *sh, char **commands)
{
	t_bg_jobs *job;

	if (!validate_options(sh, commands))
		return (0); //ensure this is right!
	job = sh->bg_node;
	while (job)
	{
        display_job_node(sh, job);
		if (job->status == DONE || job->status == TERMINATED)
			bg_node_delete(sh, &job);	
		else
			job = job->next;
	}
	sh->option_count = 0;
	sh->option = 'e';
	return (0);
}
