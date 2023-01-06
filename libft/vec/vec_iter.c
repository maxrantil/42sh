/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:04:22 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/24 19:04:52 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	vec_iter(t_vec *src, void (*f) (void *))
{
	void	*ptr;
	size_t	i;

	if (!src || !src->memory)
		return ;
	i = 0;
	while (i < src->len)
	{
		ptr = vec_get(src, i);
		f(ptr);
		i++;
	}
}
