/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:11:44 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/11 12:49:42 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*hash_check(t_session *sesh, char *program, int *hash)
{
	int		index;
	t_hash	*tmp;

	index = hash_function(program);
	if (sesh->ht[index])
	{
		tmp = sesh->ht[index];
		while (tmp)
		{
			if (ft_strequ(tmp->program, program))
			{
				tmp->hits++;
				*hash = 1;
				return (ft_strdup(tmp->path));
			}
			tmp = tmp->next;
		}
	}
	return (NULL);
}
