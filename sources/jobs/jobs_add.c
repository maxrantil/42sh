/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:14:43 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/26 13:13:51 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	jobs_add(t_job *jobs)
{
	t_job	*tmp;

	if (!jobs)
	{
		jobs = ft_init_jobs(0);
		return ;
	}
	tmp = jobs;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = ft_init_jobs(tmp->fg_group_size);
}
