/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:04:37 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/15 11:25:41 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/*
// Create a function which takes in a vector and a pointer
// to an element to be pushed to the end of the vector.
*/
int	vec_push(t_vec *dst, void *src)
{
	if (!dst || !src)
		return (-1);
	else if (!dst->memory)
		vec_new(dst, 1, dst->elem_size);
	if (dst->elem_size * dst->len >= dst->alloc_size)
		if (vec_resize(dst, dst->len * 2) < 0)
			return (-1);
	ft_memcpy(&dst->memory[dst->elem_size * dst->len], src, dst->elem_size);
	dst->len++;
	return (1);
}
