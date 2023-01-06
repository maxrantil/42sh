/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:04:11 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/24 19:04:17 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/*
// Create a function which returns an opaque handle to the element at index.
*/

void	*vec_get(t_vec *src, size_t index)
{
	if (index >= src->len || !src || !src->memory)
		return (NULL);
	return ((void *)&src->memory[src->elem_size * index]);
}
