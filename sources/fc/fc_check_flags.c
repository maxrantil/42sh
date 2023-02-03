/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:20:17 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/03 15:48:58 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/* static int	loop_flags(t_shell *sh, char ***cmd)
{
	int	i;

	i = 1;
	while ((*cmd)[1][i])
	{
		if ((*cmd)[1][i] == 's')
			return (fc_s_flag(sh, cmd));
		else
			return (fc_list_flags(sh, cmd));
	}
	return (0);
}

int	fc_check_flags(t_shell *sh, char ***cmd)
{
	int	i;

	if (*cmd && ft_strnequ((*cmd)[1], "-", 1)) // add check for -- flag
	{
		i = 1;
		while ((*cmd)[1][i])
		{
			if ((*cmd)[1][i] != 's' && (*cmd)[1][i] != 'l' \
				&& (*cmd)[1][i] != 'n' && (*cmd)[1][i] != 'r')
			{
				ft_putstr_fd("42sh: fc: invalid option", 2);
				ft_putstr_fd("fc: usage: fc [-e ename] [-lnr] ", 2);
				ft_putendl_fd("[first] [last] or fc -s [pat=rep] [command]", 2);
				return (0);
			}
			i++;
		}
	}
	return (loop_flags(sh, cmd));
} */
