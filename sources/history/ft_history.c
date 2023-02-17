/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:38:04 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/17 16:42:27 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	too_many_args(void)
{
	ft_putendl_fd("42sh: history: too many arguments", 2);
	return (0);
}

static void	print_history(t_term *t)
{
	int		i;

	i = 0;
	if (t->history_size > 500)
		i = t->history_size - 500;
	while (t->history_arr[i])
	{
		ft_printf("%4d %s\n", i + 1, t->history_arr[i]);
		i++;
	}
}

/*
 * It prints the history of the shell
 *
 * @param t the terminal structure
 */
int	ft_history(t_term *t, char **cmd)
{
	int		i;

	if (cmd[1] && ft_strnequ(cmd[1], "-c", 2))
	{
		i = 0;
		while (t->history_arr[i])
		{
			ft_strdel(&t->history_arr[i]);
			t->history_arr[i] = NULL;
			i++;
		}
		t->history_size = 0;
		return (0);
	}
	else if (cmd[1])
		return (too_many_args());
	print_history(t);
	return (0);
}
