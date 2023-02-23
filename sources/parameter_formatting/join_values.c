/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:57:45 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/23 21:35:18 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

static int	substitute_value(t_param *pa, int *ret)
{
	char	*temp;
	char	*subs;

	subs = substitute_or_create(g_sh, pa->subs, ret);
	temp = ft_strjoin(pa->expanded, subs);
	if (temp == NULL)
		return (1);
	ft_strdel(&subs);
	ft_strdel(&pa->expanded);
	pa->expanded = ft_strdup(temp);
	ft_strdel(&temp);
	return (0);
}

static int	substitute_substring(t_param *pa, int *ret)
{
	char	*temp;
	char	*subs;

	subs = search_from_var(g_sh, pa->subs, ret);
	if (!subs)
		return (1);
	temp = ft_strjoin(pa->expanded, subs);
	ft_strdel(&pa->expanded);
	pa->expanded = ft_strdup(temp);
	if (subs)
		ft_strdel(&subs);
	ft_strdel(&temp);
	return (0);
}

static void	init_join(t_param *pa)
{
	ft_strdel(&pa->subs);
	pa->subs = ft_strjoin(pa->var, pa->expanded);
	ft_strdel(&pa->var);
	pa->oper = get_operator(pa->subs);
	ft_strdel(&pa->expanded);
	pa->expanded = ft_strnew(1);
}

int	join_values(t_shell *sh, t_param *pa, char *cmd, int *ret)
{
	init_join(pa);
	if (pa->oper[0] == GET_VALUE)
	{
		if (substitute_value(pa, ret))
		{
			ft_strdel(&pa->subs);
			return (1);
		}
	}
	else if (pa->oper[0] == SUBSTRING_BEGIN || pa->oper[0] == SUBSTRING_END)
	{
		if (substitute_substring(pa, ret))
			return (1);
	}
	else if (ft_strnequ(pa->subs, STRING_LEN, 2))
		variable_length(pa->subs, pa);
	else
		pa->expanded = ft_expansion_dollar(sh, cmd);
	if (!pa->expanded && !*pa->expanded)
		pa->expanded = ft_strnew(1);
	ft_strdel(&pa->subs);
	return (0);
}
