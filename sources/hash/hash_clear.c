/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:40:46 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/30 11:41:12 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	hash_clear(t_hash **ht)
{
	t_hash	*tmp;
	t_hash	*tmp2;
	int		i;

	i = -1;
	while (++i < HASH_SIZE)
	{
		if (ht[i])
		{
			tmp = ht[i];
			while (tmp)
			{
				tmp2 = tmp->next;
				tmp->hits = 0;
				free(tmp->program);
				free(tmp->path);
				free(tmp);
				tmp = tmp2;
			}
			ht[i] = NULL;
		}
	}
}
