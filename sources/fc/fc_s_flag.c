/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_s_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:18:26 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 18:24:34 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	fc_use_last_match(t_shell *sh, char ***cmd, int y)
{
	ft_freeda((void ***)cmd, calc_chptr(*cmd));
	*cmd = \
	ft_strsplit(sh->term->history_arr[y], ' ');
	if (!*cmd)
		fc_print_error(3);
	fc_update_history(sh, cmd);
}

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
			fc_use_last_match(sh, cmd, y);
			break ;
		}
		y--;
	}
	if (y == 0)
		return (fc_print_error(5));
	return (1);
}

static int	fc_s_only(t_shell *sh, char ***cmd)
{
	ft_strdel(&sh->term->history_arr[sh->term->history_size - 1]);
	sh->term->history_arr[sh->term->history_size - 1] = \
	ft_strdup(sh->term->history_arr[sh->term->history_size - 2]);
	ft_freeda((void ***)cmd, calc_chptr(*cmd));
	ft_putendl(sh->term->history_arr[sh->term->history_size - 2]);
	*cmd = \
	ft_strsplit(sh->term->history_arr[sh->term->history_size - 2], ' ');
	if (!*cmd)
		fc_print_error(3);
	return (1);
}

int	fc_s_flag(t_shell *sh, char ***cmd)
{
	int	i;

	if (*(cmd) && (*cmd)[1] && !(*cmd)[2])
		return (fc_s_only(sh, cmd));
	i = 2;
	while ((*cmd)[i] && ft_strchr((*cmd)[i], '='))
		i++;
	if ((*cmd)[i])
		return (find_matching(sh, (*cmd)[i], cmd));
	else if (ft_strchr((*cmd)[2], '='))
		return (fc_s_change(sh, cmd));
	return (0);
}
