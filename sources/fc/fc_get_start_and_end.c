/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_get_start_and_end.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:05:33 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/13 17:49:39 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	no_argument(t_shell *sh, t_fc *fc)
{
	fc->start = (int)sh->term->history_size - 3;
	fc->end = (int)sh->term->history_size - 1;
}

static void	one_argument(t_shell *sh, t_fc *fc, char ***cmd)
{
	int		num;

	num = ft_atoi((*cmd)[fc->flags + fc->e]);
	if (num == 0)
	{
		fc->start = (int)sh->term->history_size - 3;
		fc->end = (int)sh->term->history_size - 1;
	}
	else if (num < 0)
	{
		if (num * -1 > (int)sh->term->history_size)
			fc->start = 0;
		else
			fc->start = (int)sh->term->history_size + num - 2;
		fc->end = fc->start + 2;
	}
	else
	{
		if (num > (int)sh->term->history_size)
			fc->start = (int)sh->term->history_size - 3;
		else
			fc->start = num - 2;
		fc->end = fc->start + 2;
	}
}

static void	get_fc_end(t_shell *sh, t_fc *fc, int num2)
{
	if (num2 == 0)
		fc->end = (int)sh->term->history_size - 1;
	else if (num2 < 0)
	{
		if (num2 * -1 > (int)sh->term->history_size)
			fc->end = 0;
		else
			fc->end = (int)sh->term->history_size + num2 - 1;
	}
	else
	{
		if (num2 > (int)sh->term->history_size)
			fc->end = (int)sh->term->history_size - 1;
		else
			fc->end = num2;
	}
}

static int	two_argument(t_shell *sh, t_fc *fc, char ***cmd)
{
	int		num;
	int		num2;

	num = ft_atoi((*cmd)[fc->flags + fc->e]);
	num2 = ft_atoi((*cmd)[fc->flags + 1 + fc->e]);
	if (num2 < num)
		return (-1);
	if (num == 0)
		fc->start = (int)sh->term->history_size - 3;
	else if (num < 0)
	{
		if (num * -1 > (int)sh->term->history_size)
			fc->start = -1;
		else
			fc->start = (int)sh->term->history_size + num - 2;
	}
	else
	{
		if (num > (int)sh->term->history_size)
			fc->start = -1;
		else
			fc->start = num - 2;
	}
	get_fc_end(sh, fc, num2);
	// ft_printf("start: %d, end: %d\n", fc->start, fc->end);
	return (1);
}

int	fc_get_start_and_end(t_shell *sh, t_fc *fc, char ***cmd)
{
	if (!(*cmd)[fc->flags + fc->e])
		no_argument(sh, fc);
	else if ((*cmd)[fc->flags + fc->e] && !(*cmd)[fc->flags + 1 + fc->e])
	{
		if (int_check_validity((*cmd)[fc->flags + fc->e], "fc") == 2)
			return (0);
		one_argument(sh, fc, cmd);
	}
	else if ((*cmd)[fc->flags + fc->e] && (*cmd)[fc->flags + 1 + fc->e])
	{
		if (int_check_validity((*cmd)[fc->flags + fc->e], "fc") == 2 \
		|| int_check_validity((*cmd)[fc->flags + 1 + fc->e], "fc") == 2)
			return (0);
		if (two_argument(sh, fc, cmd) < 0)
		{
			ft_putendl_fd("42sh: fc: first argument must be smaller than second", 2);
			return (0);
		}
	}
	else
		return (0);
	return (1);
}
