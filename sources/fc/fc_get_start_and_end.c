/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_lflag_get_start_and_end.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:13:55 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/15 13:32:39 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	get_pivot(t_shell *sh, char *cmd)
{
	int	start;

	start = ft_atoi(cmd);
	if (start == 0 || start == -1 || start > (int)sh->term->history_size)
		start = sh->term->history_size - 2;
	if (start < -1)
	{
		start = sh->term->history_size + start;
		if (start < 0)
			return (0);
	}
	return (start - 1);
}

void	fc_get_start_and_end(t_shell *sh, t_fc *fc, char ***cmd)
{
	char	*cmd1;
	char	*cmd2;

	cmd1 = (*cmd)[fc->flags + fc->e];
	cmd2 = (*cmd)[fc->flags + fc->e + 1];
	fc->start = 0;
	fc->end = sh->term->history_size - 2;
	if (!cmd1)
	{
		if (sh->term->history_size > FC_LEN)
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
