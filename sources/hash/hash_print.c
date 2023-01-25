/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:10:49 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/11 12:51:06 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	print_table(t_hash **ht)
{
	int		i;
	t_hash	*tmp;

	i = -1;
	while (++i < HASH_SIZE)
	{
		if (ht[i] != NULL)
		{
			tmp = ht[i];
			while (tmp != NULL)
			{
				ft_printf("%d	%s\n", tmp->hits, tmp->path);
				tmp = tmp->next;
			}
		}
	}
}

void	hash_print(t_hash **ht)
{
	int		i;

	i = -1;
	while (++i < HASH_SIZE)
	{
		if (ht[i])
		{
			ft_printf("hits    command\n");
			break ;
		}
	}
	if (i == HASH_SIZE)
	{
		ft_putstr_fd("21sh: hash table empty\n", 2);
		return ;
	}
	print_table(ht);
}
