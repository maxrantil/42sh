/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/01/25 15:01:28 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "keyboard.h"

static void	add_to_capped_history(t_term *t, char *command)
{
	char	**temp;
	int		i;
	int		j;

	temp = (char **)malloc(sizeof(char *) * (MAX_HISTORY + 1));
	if (!temp)
	{
		ft_putendl_fd("21sh: malloc error, add_to_capped_history()", 2);
		exit(1);
	}
	i = MAX_HISTORY / 2;
	j = 0;
	while (t->history_arr[++i])
		temp[j++] = ft_strdup(t->history_arr[i]);
	temp[j++] = ft_strdup(command);
	temp[j] = NULL;
	t->history_size = j;
	ft_arrclean(t->history_arr);
	t->history_arr = temp;
}

static void	increase_history_size(t_term *t)
{
	char	**temp;
	int		i;

	temp = (char **)malloc(sizeof(char *) * (t->history_size + 2));
	if (temp)
	{
		i = -1;
		while (t->history_arr[++i])
			temp[i] = ft_strdup(t->history_arr[i]);
		temp[i] = NULL;
		ft_arrclean(t->history_arr);
		t->history_arr = temp;
	}
	else
	{
		ft_putendl_fd("21sh: malloc error, increase_history_size()", 2);
		exit(1);
	}
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
		increase_history_size(t);
		t->history_arr[t->history_size] = ft_strdup(command);
		t->history_size++;
		t->history_arr[t->history_size] = NULL;
	}
	else
		add_to_capped_history(t, command);
}
