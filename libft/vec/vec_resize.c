/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:05:01 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/24 19:05:02 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/*
// Create a function which will take in a target_size parameter
// and either shrink (destructively) or grow the vector to the target size,
// copying the old contents over to the new allocation.
*/

int	vec_resize(t_vec *src, size_t target_size)
{
	t_vec	dst;

	if (!src)
		return (-1);
	else if (!src->memory)
		return (vec_new(src, target_size, src->elem_size));
	else if (vec_new(&dst, target_size, src->elem_size) < 0)
		return (-1);
	ft_memcpy(dst.memory, src->memory, src->alloc_size);
	dst.len = src->len;
	vec_free(src);
	*src = dst;
	return (target_size);
}
