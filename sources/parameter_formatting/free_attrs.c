/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_attrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:45:44 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/11 11:20:36 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	free_attrs(t_param *pa, char **new_cmd)
{
	int	k;

	k = 0;
	while (k < 100)
		ft_strdel(&pa->list[k++]);
	free(pa->list);
	ft_strdel(&pa->expanded);
	ft_strdel(&(*new_cmd));
}
