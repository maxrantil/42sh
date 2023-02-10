/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pa_ints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:42:48 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 11:43:03 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void init_pa_ints(t_pa_ints *ints, char **new_cmd)
{
	ints->err = 0;
	ints->i = -1;
	ints->j = 0;
	ints->ret = 0;
	(*new_cmd) = NULL;
}