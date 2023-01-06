/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:03:23 by mrantil           #+#    #+#             */
/*   Updated: 2022/08/24 19:03:50 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/*
// Create a function that frees the allocated
// resources in src and zeroes its fields.
*/

void	vec_free(t_vec *src)
{
	if (!src || src->alloc_size == 0)
		return ;
	ft_memdel((void *)&src->memory);
	src->elem_size = 0;
	src->alloc_size = 0;
	src->len = 0;
}
