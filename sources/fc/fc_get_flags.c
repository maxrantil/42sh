/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:56:45 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/13 11:27:02 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	usage(void)
{
	ft_putendl_fd("42sh: fc: invalid option", 2);
	ft_putstr_fd("fc: usage: fc [-e ename] [-lnr] ", 2);
	ft_putendl_fd("[first] [last] or fc -s [pat=rep] [command]", 2);
	return (0);
}

static int	turn_on_flags(t_fc *fc, char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str == 's')
			fc->s = true;
		else if (*str == 'l')
			fc->l = true;
		else if (*str == 'r')
			fc->r = true;
		else if (*str == 'n')
			fc->n = true;
		else if (*str == 'e')
			fc->e = 1;
		else
			return (usage());
		str++;
	}
	return (1);
}

int	fc_get_flags(t_fc *fc, char **cmd)
{
	int		i;
	int		j;

	i = 1;
	if (cmd && cmd[i])
	{
		j = 0;
		while (cmd[i] && cmd[i][j] && cmd[i][j] == '-')
		{
			j++;
			if (cmd[i] && cmd[i][j] == '-')
			{
				++i;
				break ;
			}
			if (!turn_on_flags(fc, &cmd[i][j]))
				return (0);
			i++;
			j = 0;
		}
	}
	fc->flags = i;
	return (1);
}
