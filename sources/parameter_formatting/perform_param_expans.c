/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_param_expans.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:38:41 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/13 13:02:11 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell *g_sh;

static void retoken_into_list(t_param *pa)
{
	int i;
	int j;

	i = 0;
	j = 0;
	// if (!pa->subs[0])
	// 	pa->list[i] = retokenize(pa->var, &j);
	while (pa->subs[j])
	{
		pa->list[i++] = retokenize(pa->subs, &j);
	}
}

int	perform_param_expans(char *cmd, t_param *pa, int *ret)
{
	int	err;

	err = 0;
	if (!splitter(cmd, pa, ret) && *ret == 0)
		;
	else
		return (-1);
	if (*ret == 0)
		retoken_into_list(pa);
	if (expander(pa, *ret))
	{
		;
	}
	if (*ret == 0 && join_values(g_sh, pa, cmd, *ret))
		err = -1;
	if (*ret == 1)
	{
		err = -1;
	}
	return (err);
}
