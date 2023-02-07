/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_info_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:49:07 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/06 19:25:39 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static t_bg_jobs	*get_latest_job(t_shell *sh)
{
	t_bg_jobs	*ptr;

	ptr = sh->bg_node;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void	display_bg_job(t_shell *sh)
{
	t_bg_jobs	*ptr;

	ptr = get_latest_job(sh);
	ft_printf("[%d] %d\n", ptr->index + 1, ptr->gpid);
}

void	display_suspended_job(t_shell *sh) // This needs to updated
{
	t_bg_jobs	*ptr;

	if (sh->fg_node->gpid == 0)
	{
		display_job_node(sh, get_latest_job(sh));
		return ;
	}
	ptr = sh->bg_node;
	while (ptr)
	{
		if (ptr->gpid == sh->fg_node->gpid)
			break ;
		ptr = ptr->next;
	}
	if (ptr)
		display_job_node(sh, ptr);	
}

void	display_pipeline_cmd(t_bg_jobs *job)
{
	char	***cmd;

	cmd = job->cmd;
	while (*cmd)
	{
		ft_print_dbl_array(*(cmd++));
		if (*(cmd))
			ft_putstr(" | ");
	}
	ft_printf(" &\n");
}
