/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:56:45 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/16 12:17:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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
			fc->e = true;
		else
			return (fc_usage(*str, "invalid option"));
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
			if (turn_on_flags(fc, &cmd[i][j]) == -1)
				return (-1);
			j = 0;
			i++;
		}
	}
	fc->flags = i;
	return (1);
}
