/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:54 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/11 17:14:44 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	validate_options(t_shell *session, char **commands)
{
	int		i;

	i = 1;
	session->option = 'e';
	while (commands[i] && commands[i][0] == '-')
	{
		if (ft_strequ(commands[i], "--"))
		{
			i++;
			break ;
		}
		if (str_only_contains_chars(commands[i], "lp", session) == 0)
		{
			print_usage("jobs", session->option);
			return (0);
		}
		if (commands[i][0] != '-' || \
		!str_only_contains_chars(commands[i], "lp", session))
			break ;
		session->option = commands[i][ft_strlen(commands[i]) - 1];
		i++;
	}
	session->option_count = i - 1;
	return (1);
}

static void	display_no_flags(t_shell *sh)
{
	t_bg_jobs	*job;

	job = sh->bg_node;
	while (job)
	{
		display_job_node(sh, job);
		if (job->status == DONE || job->status == TERMINATED)
			bg_node_delete(sh, &job);
		else
			job = job->next;
	}
}

static void	display_l_flags(t_shell *sh)
{
	t_bg_jobs	*job;

	job = sh->bg_node;
	while (job)
	{
		display_job_pipeline(sh, job);
		if (job->status == DONE || job->status == TERMINATED)
			bg_node_delete(sh, &job);
		else
			job = job->next;
	}
}

static void	display_p_flags(t_shell *sh)
{
	t_bg_jobs	*job;

	job = sh->bg_node;
	while (job)
	{
		ft_printf("%d\n", *job->pid);
		if (job->status == DONE || job->status == TERMINATED)
			bg_node_delete(sh, &job);
		else
			job = job->next;
	}
}

int	ft_jobs(t_shell *sh, char **commands)
{
	if (!validate_options(sh, commands))
		return (0);
	if (sh->option == 'l')
		display_l_flags(sh);
	else if (sh->option == 'p')
		display_p_flags(sh);
	else
		display_no_flags(sh);
	sh->option_count = 0;
	sh->option = 'e';
	return (0);
}
