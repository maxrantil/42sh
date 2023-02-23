/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:29:33 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/23 13:30:00 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

int	expander(t_param *pa, int *ret)
{
	int	i;

	i = -1;
	while (pa->list[++i])
	{
		if (ft_strnequ(pa->list[i], "${", 2))
			param_format(&pa->list[i]);
		pa->expanded = ft_strupdate(pa->expanded, pa->list[i]);
		if (*ret == -1 || !*pa->expanded)
			return (1);
	}
	return (0);
}

	// if ((ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == '#') || (ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == '%'))
		// {
		// 	ft_printf("2\n");
		// 	// if (substring_substitution(pa, ret, pa->list[i]))
		// 	// 	return (1);
		// }
//		ft_printf("before strnw%s\n", pa->list[i]);
		// if (ft_strnequ(pa->list[i], "${", 2))
		// {
			// ft_printf("2.5\n");
			// if (substitute_value(pa, ret, pa->list[i]))
			// 	return (1);
		// }
		// else
		// {
//			ft_printf("3\n");

// ft_printf("1    %s\n", pa->list[i]);
// pa->flag = get_flag(pa->list[i], ret);
