/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:00:54 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/13 09:11:03 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static t_bg_jobs	*job_delete_done(t_shell *sh, t_bg_jobs *job)
{
	if (job->status == DONE || job->status == TERMINATED \
	|| job->status == EXITED)
		bg_node_delete(sh, &job);
	else
		job = job->next;
	return (job);
}

static int	validate_options(t_shell *sh, char **commands)
{
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	while (commands[++i])
	{
		if (ft_strequ(commands[i], "--"))
		{
			i++;
			break ;
		}
		if (commands[i][0] != '-')
			break ;
		if (str_only_contains_chars(commands[i], "lp", sh) == 0)
		{
			ret = 0;
			continue ;
		}
		sh->option = commands[i][ft_strlen(commands[i]) - 1];
	}
	sh->option_count = i;
	return (ret);
}

static void	display_job_with_flags(t_shell *sh, t_bg_jobs *job)
{
	if (sh->option == 'l')
		display_job_pipeline(sh, job);
	else if (sh->option == 'p')
		ft_printf("%d\n", *job->pid);
	else
		display_job_node(sh, job);
}

static void	display_fetched_jobs(t_shell *sh, char **cmd)
{
	int			i;
	t_bg_jobs	*job;

	i = -1;
	job = NULL;
	while (cmd[++i])
	{
		if (*(cmd[i]) == '-')
			job = sh->bg_node;
		else
			job = bg_fetch_node(sh, cmd[i], "jobs");
		if (job)
			display_job_with_flags(sh, job);
	}
}

int	ft_jobs(t_shell *sh, char **commands)
{
	t_bg_jobs	*job;
	bool		skip;

	skip = false;
	if (!validate_options(sh, commands))
	{
		print_usage("jobs", sh->option);
		skip = true;
	}
	if (commands[sh->option_count])
	{
		display_fetched_jobs(sh, &commands[sh->option_count]);
		return (0);
	}
	if (skip)
		return (0);
	job = sh->bg_node;
	while (job)
	{
		display_job_with_flags(sh, job);
		job = job_delete_done(sh, job);
	}
	sh->option_count = 0;
	sh->option = 'e';
	return (0);
}
