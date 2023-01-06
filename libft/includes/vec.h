/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:07:48 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/18 14:32:08 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "libft.h"

typedef struct s_vec
{
	unsigned char	*memory;
	size_t			elem_size;
	size_t			alloc_size;
	size_t			len;
}	t_vec;

int		vec_new(t_vec *src, size_t init_len, size_t elem_size);
void	vec_free(t_vec *src);
int		vec_from(t_vec *dst, void *src, size_t len, size_t elem_size);
int		vec_resize(t_vec *src, size_t target_size);
void	*vec_get(t_vec *src, size_t index);
int		vec_push(t_vec *src, void *elem);
void	vec_iter(t_vec *src, void (*f) (void *));
void	vec_sort(t_vec *src, int (*f)(void *, void *));

#endif
