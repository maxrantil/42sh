/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_get_start_for_lists.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:13:55 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 18:33:47 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	null_check_first(t_shell *sh, char *cmd)
{
	int	start;

	if (ft_atoi(cmd) == 0)
	{
		start = sh->term->history_size - 3;
		sh->term->history_size -= 1;
	}
	else
		start = ft_atoi(cmd) - 2;
	if (start < -1)
	{
		start = sh->term->history_size + start;
		if (start < 0)
			start = -1;
	}
	return (start);
}

static int	null_check_last(t_shell *sh, char *cmd)
{
	int	last;

	if (ft_atoi(cmd) == 0)
		last = sh->term->history_size;
	else
	{
		last = ft_atoi(cmd) + 1;
		if (last > (int)sh->term->history_size)
			last = sh->term->history_size;
	}
	if (last <= 0)
		last = sh->term->history_size;
	return (last);
}

int	fc_get_start_for_lists(t_shell *sh, char ***cmd) //need more handling with too big numbers
{
	int	start;

	if ((*cmd)[0] && (*cmd)[1] && (*cmd)[2] && !(*cmd)[3])
		start = null_check_first(sh, (*cmd)[2]);
	else if ((*cmd)[0] && (*cmd)[1] && (*cmd)[2] && (*cmd)[3])
	{
		start = null_check_first(sh, (*cmd)[2]);
		sh->term->history_size = null_check_last(sh, (*cmd)[3]);
	}
	else if (sh->term->history_size > FC_LEN)
		start = sh->term->history_size - FC_LEN;
	else
		start = -1;
	return (start);
}
