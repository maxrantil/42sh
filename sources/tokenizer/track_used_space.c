/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_used_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:43:28 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/11 13:08:46 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	track_used_space(t_token **args, size_t current_pointer_n
	, size_t *max_pointer_n)
{
	size_t	new_size;
	size_t	growth;
	t_token	*new_args;
	size_t	i;

	growth = 2;
	i = 0;
	if (current_pointer_n >= *max_pointer_n)
	{
		new_size = sizeof(**args) * ((*max_pointer_n)
				+ ((*max_pointer_n) * growth));
		new_args = (t_token *)ft_memalloc(new_size);
		while (i <= current_pointer_n)
		{
			new_args[i] = (*args)[i];
			++i;
		}
		*max_pointer_n = (*max_pointer_n) * growth;
		free(*args);
		*args = new_args;
	}
}
