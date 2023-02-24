/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param_format_seq.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:29:33 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/23 13:30:20 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

int	check_param_format_seq(t_param *pa)
{
	int	i;

	i = -1;
	while (pa->list[++i])
	{
		if (ft_strnequ(pa->list[i], "${", 2))
			param_format(&pa->list[i]);
		pa->expanded = ft_strupdate(pa->expanded, pa->list[i]);
		if (!*pa->expanded)
			return (1);
	}
	return (0);
}
