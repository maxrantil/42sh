/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:35:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 17:31:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	init_ht(t_hash ***ht)
{
	int	i;

	*ht = (t_hash **)malloc(sizeof(t_hash *) * (HASH_SIZE + 1));
	i = 0;
	while (i <= HASH_SIZE)
		(*ht)[i++] = NULL;
}

void	hash_init(t_session *sesh)
{
	t_hash	**ht;

	ht = NULL;
	sesh->ht = ht;
	init_ht(&sesh->ht);
}
