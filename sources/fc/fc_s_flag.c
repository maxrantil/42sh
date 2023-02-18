/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_s_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:18:26 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/17 18:20:19 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// static char	**fc_use_last_match(t_shell *sh, char ***cmd, int y)
// {
// 	char **ret;

// 	// ft_freeda((void ***)cmd, calc_chptr(*cmd));
// 	ret = \
// 	ft_strsplit(sh->term->history_arr[y], ' ');
// 	fc_update_history(sh, cmd);
// 	return (ret);
// }

static int	find_matching(t_shell *sh, char *str, char ***cmd)
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
		{
			return (y);
			// return (fc_use_last_match(sh, cmd, y));
			// break ;
		}
		y--;
	}
	if (y == 0)
		return (fc_print_error(5));
	return (2); // check this
}

static int	fc_s_only(t_shell *sh, char ***cmd, int y)
{
	ft_strdel(&sh->term->history_arr[sh->term->history_size - 1]);
	sh->term->history_arr[sh->term->history_size - 1] = \
	ft_strdup(sh->term->history_arr[sh->term->history_size - y]);
	ft_arrclean(*cmd);
	ft_putendl_fd(sh->term->history_arr[sh->term->history_size - y], 2);
	*cmd = \
	ft_strsplit(sh->term->history_arr[sh->term->history_size - y], ' ');
	return (1);
}

int	fc_s_flag(t_shell *sh, t_fc *fc, char ***cmd)
{
	int		i;
	int		y;

	y = 2;
	if (!(*cmd)[fc->flags])
		return (fc_s_only(sh, cmd, y));
	i = fc->flags;
	if ((*cmd)[i] && ft_strchr((*cmd)[i], '='))
	{
		while ((*cmd)[i] && ft_strchr((*cmd)[i], '='))
			i++;
		if ((*cmd)[i])
			y = find_matching(sh, (*cmd)[i], cmd);
	}
	if (ft_strchr((*cmd)[fc->flags], '='))
		return (fc_s_change(sh, fc, cmd, y));
	return (fc_s_only(sh, cmd, y));
}
