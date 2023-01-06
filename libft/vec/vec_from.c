/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_from.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:03:58 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/24 19:04:06 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/*
// Create a function vec_from which takes in a pointer to some memory, 
// which then will be copied over to the new vector.
*/

int	vec_from(t_vec *dst, void *src, size_t len, size_t elem_size)
{
	if (!dst || !src || len == 0 || elem_size == 0)
		return (-1);
	else if (vec_new(dst, len, elem_size) < 0)
		return (-1);
	ft_memcpy(dst->memory, src, dst->alloc_size);
	dst->len = len;
	return (dst->alloc_size);
}
