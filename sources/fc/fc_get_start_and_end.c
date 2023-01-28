/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_get_start_and_end.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:05:33 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 14:20:22 by mrantil          ###   ########.fr       */
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
	if ((*cmd)[1 + fc->e][0] == '-')
	{
		fc->start = (int)sh->term->history_size \
		+ ft_atoi((*cmd)[1 + fc->e]) - 2;
		fc->end = fc->start + 2;
	}
	else
	{
		fc->start = ft_atoi((*cmd)[1 + fc->e]) - 2;
		fc->end = ft_atoi((*cmd)[1 + fc->e]);
	}
}

static void	two_argument(t_shell *sh, t_fc *fc, char ***cmd)
{
	if ((*cmd)[1 + fc->e][0] == '-')
		fc->start = (int)sh->term->history_size \
		+ ft_atoi((*cmd)[1 + fc->e]);
	else
		fc->start = ft_atoi((*cmd)[1 + fc->e]) - 2;
	if ((*cmd)[2 + fc->e][0] == '-')
	{
		if ((*cmd)[1 + fc->e][0] == '-')
			fc->end = (int)sh->term->history_size \
			+ ft_atoi((*cmd)[2 + fc->e]) - 2;
		else
			fc->end = (int)sh->term->history_size \
			+ ft_atoi((*cmd)[2 + fc->e]) - 1;
	}
	else
	{
		if ((*cmd)[1 + fc->e][0] == '-')
			fc->end = ft_atoi((*cmd)[2 + fc->e]) - 2;
		else
			fc->end = ft_atoi((*cmd)[2 + fc->e]);
	}
}

int	fc_get_start_and_end(t_shell *sh, t_fc *fc, char ***cmd)
{
	if (!(*cmd)[1 + fc->e])
		no_argument(sh, fc);
	else if ((*cmd)[1 + fc->e] && !(*cmd)[2 + fc->e])
		one_argument(sh, fc, cmd);
	else if ((*cmd)[1 + fc->e] && (*cmd)[2 + fc->e])
		two_argument(sh, fc, cmd);
	else
		return (0);
	return (1);
}
