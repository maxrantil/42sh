/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:07:03 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/30 12:07:25 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	hash_free(t_hash **ht)
{
	t_hash	*tmp;
	int		i;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (ht[i])
		{
			tmp = ht[i];
			while (tmp)
			{
				ft_strdel(&tmp->program);
				ft_strdel(&tmp->path);
				ft_memdel((void **)tmp);
				tmp = tmp->next;
			}
		}
		i++;
	}
	free(ht);
}
