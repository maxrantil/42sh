/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:38:01 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/20 15:16:13 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

static void	add_to_capped_history(t_term *t)
{
	int		j;

	j = 0;
	while (j < (MAX_HISTORY / 2))
	{
		ft_strdel(&(t->history_arr[j]));
		t->history_arr[j] = t->history_arr[j + (MAX_HISTORY / 2)];
		t->history_arr[j + (MAX_HISTORY / 2)] = NULL;
		j++;
	}
	t->history_size = j;
}

void	ft_history_add_command(t_term *t, char *command)
{
	int	i;

	i = 0;
	if (t->history_size < MAX_HISTORY)
	{
		while (command[i] && ft_isspace(command[i]))
			i++;
		if (!command[i])
			return ;
		t->history_arr[t->history_size] = ft_strdup(command);
		t->history_size++;
	}
	else
		add_to_capped_history(t);
}
