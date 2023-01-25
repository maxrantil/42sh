/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_init_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:35:59 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/11 11:35:45 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * It takes a hash table and a new hash table entry, and inserts the new entry
 * into the hash table
 */
static void	ht_insert(t_session *sesh, t_hash *new)
{
	size_t	index;

	index = hash_function(new->program);
	new->next = sesh->ht[index];
	sesh->ht[index] = new;
}

/*
 * It creates a new hash table entry, and inserts it into the hash table
 */
void	hash_init_struct(t_session *sesh, char *exepath, int hits)
{
	char	*program;
	t_hash	*new;

	if (ft_strrchr(exepath, '/'))
		program = ft_strdup(ft_strrchr(exepath, '/') + 1);
	else
		program = ft_strdup(exepath);
	if (!ft_strequ(program, "hash"))
	{
		new = (t_hash *)malloc(sizeof(t_hash));
		if (!new)
		{
			ft_putstr_fd("malloc fail on init_ht_struct\n", 2);
			exit(1);
		}
		new->program = program;
		new->path = ft_strdup(exepath);
		new->hits = hits;
		new->next = NULL;
		ht_insert(sesh, new);
	}
}
