/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:43:17 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 11:43:39 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void init_pa(t_param *pa)
{
	pa->subs = NULL;
	pa->strip = NULL;
	pa->var = NULL;
	pa->list = (char **)ft_memalloc(sizeof(char *) * 100);
	pa->expanded = ft_strnew(1);
	pa->op = 0;
}