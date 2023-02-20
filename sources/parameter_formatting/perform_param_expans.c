/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_param_expans.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:38:41 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/20 18:01:40 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

static void	retoken_into_list(t_param *pa)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
	expander(pa, *ret);
	if (*ret == 0 && join_values(g_sh, pa, cmd, *ret))
		err = -1;
	if (*ret == 1)
		err = -1;
	return (err);
}
