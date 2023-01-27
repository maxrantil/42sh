/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:46:13 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/26 13:12:05 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_job *ft_init_jobs(int group_size)
{
	t_job *jobs;

	jobs = (t_job *)ft_memalloc(sizeof(t_job));
	jobs->next = NULL;
	ft_memset(jobs->fg_group, -1, JOBS_MAX);
	jobs->fg_group_size = ++group_size;
	jobs->cmd = NULL;
	return (jobs);
}
