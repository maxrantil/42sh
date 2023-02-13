/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_lflag_get_start_and_end.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:13:55 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/13 11:27:41 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	get_start(t_shell *sh, char *cmd)
{
	int	start;

	start = ft_atoi(cmd);
	if (start == 0)
		start = sh->term->history_size - 3;
	else if (start > (int)sh->term->history_size)
		start = -1;
	else
		start -= 2;
	if (start < -1)
	{
		start = sh->term->history_size + start;
		if (start < 0)
			start = -1;
	}
	return (start);
}

static int	get_end(t_shell *sh, char *cmd)
{
	int	end;

	end = ft_atoi(cmd);
	if (end <= 0)
		end = sh->term->history_size;
	else
	{
		end += 1;
		if (end > (int)sh->term->history_size)
			end = sh->term->history_size;
	}
	return (end);
}

int	fc_lflag_get_start_and_end(t_shell *sh, t_fc *fc, char ***cmd)
{
	fc->start = -1;
	if (!(*cmd)[fc->flags])
	{
		if (sh->term->history_size > FC_LEN)
			fc->start = sh->term->history_size - FC_LEN;
	}
	else if ((*cmd)[fc->flags] && !(*cmd)[fc->flags + 1])
	{
		fc->start = get_start(sh, (*cmd)[fc->flags]);
	}
	else if ((*cmd)[fc->flags] && (*cmd)[fc->flags + 1])
	{
		fc->start = get_start(sh, (*cmd)[fc->flags]);
		fc->end = get_end(sh, (*cmd)[fc->flags + 1]);
	}
	return (fc->start);
}
