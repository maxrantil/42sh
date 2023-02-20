/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_get_start_and_end.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:13:55 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/20 12:57:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	get_history_cap(t_shell *sh)
{
	if (sh->term->history_size < 500)
		return (0);
	else
		return (sh->term->history_size - 500);
}

static int	int_check(char *arg)
{
	long		arg_long;

	arg_long = ft_atol(arg);
	if (arg_long < INT_MIN)
		return (INT_MIN);
	else if (arg_long > INT_MAX)
		return (INT_MAX);
	return ((int)arg_long);
}

static int	get_start(t_shell *sh, char *cmd)
{
	int		start;
	int		cap;

	start = int_check(cmd);
	cap = get_history_cap(sh);
	if (start == 0)
		start = sh->term->history_size - 1;
	else if (start > 0)
	{
		if (start < cap || start > (int)sh->term->history_size)
			return (cap);
	}
	else
	{
		start = sh->term->history_size + start;
		if (start < 0)
			return (cap);
	}
	return (start - 1);
}

static int	get_end(t_shell *sh, char *cmd)
{
	long	end;
	int		cap;

	end = ft_atol(cmd);
	cap = get_history_cap(sh);
	if (end == 0)
		end = sh->term->history_size - 1;
	if (end > 0)
	{
		if (end < cap || end > (int)sh->term->history_size)
			end = sh->term->history_size - 1;
	}
	else
	{
		if (end < INT_MIN)
			end = sh->term->history_size - 1;
		else
		{
			end = sh->term->history_size + end;
			if (end < 0)
				return (cap);
		}
	}
	return (end - 1);
}

static void	get_end_default(t_shell *sh, t_fc *fc)
{
	if (fc->l)
		fc->end = sh->term->history_size - 2;
	else
		fc->end = fc->start;
}

void	fc_get_start_and_end(t_shell *sh, t_fc *fc, char ***cmd)
{
	fc->start = 0;
	if (!(*cmd)[fc->flags])
	{
		if (!fc->l)
			fc->start = sh->term->history_size - 2;
		else if (sh->term->history_size > FC_LEN)
			fc->start = sh->term->history_size - FC_LEN;
		get_end_default(sh, fc);
	}
	else if ((*cmd)[fc->flags] && !(*cmd)[fc->flags + 1])
	{
		fc->start = get_start(sh, (*cmd)[fc->flags]);
		get_end_default(sh, fc);
	}
	else if ((*cmd)[fc->flags] && (*cmd)[fc->flags + 1])
	{
		fc->start = get_start(sh, (*cmd)[fc->flags]);
		fc->end = get_end(sh, (*cmd)[fc->flags + 1]);
	}
}
