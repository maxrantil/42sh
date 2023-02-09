/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_exit_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:46:29 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/08 14:42:17 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	jobs_exit_check(t_shell *sh)
{
	t_bg_jobs	*ptr;

	ptr = sh->bg_node;
	while (ptr)
	{
		if (ptr->status == STOPPED)
		{
			if (sh->exit_confirm != ptr->index)
				sh->exit_confirm = ptr->index;
			else if (sh->exit_confirm == ptr->index)
				sh->exit_confirm = -1;
			return ;
		}
		ptr = ptr->next;
	}
	sh->exit_confirm = -1;
}
