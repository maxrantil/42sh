/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:11:44 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/26 09:56:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*hash_check(t_shell *sh, char *program, int *hash)
{
	int		index;
	t_hash	*tmp;

	index = hash_function(program);
	if (sh->ht[index])
	{
		tmp = sh->ht[index];
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
