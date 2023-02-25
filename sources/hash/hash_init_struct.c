/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_init_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:35:59 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/25 15:59:05 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
 * It takes a hash table and a new hash table entry, and inserts the new entry
 * into the hash table
 */
static void	ht_insert(t_shell *sh, t_hash *new)
{
	size_t	index;

	index = hash_function(new->program);
	new->next = sh->ht[index];
	sh->ht[index] = new;
}

/*
 * It creates a new hash table entry, and inserts it into the hash table
 */
void	hash_init_struct(t_shell *sh, char *exepath, int hits)
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
		if (sh->exit_stat == 0)
			new->hits = hits;
		else
			new->hits = 0;
		new->next = NULL;
		ht_insert(sh, new);
	}
}
