/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_s_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:18:26 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/20 15:06:48 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	find_matching(t_shell *sh, char *str)
{
	int		y;
	int		x;
	int		len;

	y = sh->term->history_size - 1;
	len = ft_strlen(str);
	while (y > 0)
	{
		x = 0;
		while (sh->term->history_arr[y][x] && str[x] \
		&& sh->term->history_arr[y][x] == str[x])
			x++;
		if (x == len)
			return (y);
		y--;
	}
	return (fc_print_error(5));
}

static int	fc_s_only(t_shell *sh, t_fc *fc , int y)
{
	ft_strdel(&sh->term->history_arr[sh->term->history_size - 1]);
	sh->term->history_arr[sh->term->history_size - 1] = \
	ft_strdup(sh->term->history_arr[y]);
	fc->ret_cmd = ft_strdup(sh->term->history_arr[y]);
	ft_putendl_fd(sh->term->history_arr[y], 2);
	fc_build_and_execute_new_tree(sh, fc);
	return (0);
}

static void	specific_in_range(t_shell *sh, int *specific)
{
	int cap;

	if (sh->term->history_size < 500)
		cap = 0;
	else
		cap = sh->term->history_size - 500;
	if (*specific < cap || *specific >= (int)sh->term->history_size)
		*specific = sh->term->history_size - 1;
	--(*specific);
}

static int	specific(t_shell *sh, t_fc *fc, char ***cmd)
{
	int	specific;

	specific = ft_atol((*cmd)[fc->flags]);
	specific_in_range(sh, &specific);
	fc_s_only(sh, fc, specific);
	return (0);
}

int	fc_s_flag(t_shell *sh, t_fc *fc, char ***cmd)
{
	int		i;
	int		y;

	y = sh->term->history_size - 2;
	if (!(*cmd)[fc->flags])
		return (fc_s_only(sh, fc, y));
	i = fc->flags;
	while ((*cmd)[i] && ft_strchr((*cmd)[i], '='))
		i++;
	if ((*cmd)[i] && (ft_isdigit((*cmd)[i][0]) || (*cmd)[i][0] == '-'))
		return (specific(sh, fc, cmd));
	else if ((*cmd)[i])
		y = find_matching(sh, (*cmd)[i]);
	if (y)
		return (fc_s_change(sh, fc, cmd, y));
	return (0);
}
