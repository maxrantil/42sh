/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_get_start_and_end.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:13:55 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/15 16:52:42 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	get_pivot(t_shell *sh, char *cmd)
{
	int	pivot;

	pivot = ft_atoi(cmd);
	if (pivot == 0 || pivot == -1 || pivot > (int)sh->term->history_size)
		pivot = sh->term->history_size - 2;
	if (pivot < -1)
	{
		pivot = sh->term->history_size + pivot;
		if (pivot < 0)
			return (0);
	}
	return (pivot - 1);
}

void	fc_get_start_and_end(t_shell *sh, t_fc *fc, char ***cmd)
{
	char	*cmd1;
	char	*cmd2;

	cmd1 = (*cmd)[fc->flags];
	cmd2 = (*cmd)[fc->flags + 1];
	fc->start = 0;
	fc->end = sh->term->history_size - 2;
	if (!cmd1)
	{
		if (!fc->l)
			fc->start = sh->term->history_size - 2;
		else if (sh->term->history_size > FC_LEN)
		 	fc->start = sh->term->history_size - FC_LEN;
	}
	else if (cmd1 && !cmd2)
		fc->start = get_pivot(sh, cmd1);
	else if (cmd1 && cmd2)
	{
		fc->start = get_pivot(sh, cmd1);
		fc->end = get_pivot(sh, cmd2);
	}
}
