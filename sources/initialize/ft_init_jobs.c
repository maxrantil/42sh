/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:46:13 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/28 15:42:35 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_job *ft_init_jobs(void)
{
	t_job *jobs;

	jobs = (t_job *)ft_memalloc(sizeof(t_job));
	jobs->shared_mem_ptr = NULL;
	jobs->shared_mem_idx_ptr = NULL;
	jobs->shared_mem_id = -1;
	jobs->shared_mem_index = -1;
	jobs->cmd = NULL;
	return (jobs);
}
