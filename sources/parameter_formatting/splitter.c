/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:19:56 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 13:23:14 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell *g_sh;

static void	first_split(char *cmd, t_param *pa, int *ret)
{
	pa->strip = ft_strdup(cmd);
	remove_braces(pa->strip);
	pa->subs = ft_strdup(get_flag(pa->strip + 1, ret));
	pa->op = pa->subs[0];
	pa->subs = (char *)ft_memmove(pa->subs, pa->subs + 1, ft_strlen(pa->subs));
	pa->var = ft_strndup(pa->strip, ft_strlen(pa->strip) - (ft_strlen(pa->subs)));
}

static void regular_dollar_expansion(char *cmd, t_param *pa, int *ret)
{
	ft_strdel(&pa->expanded);
	pa->strip = ft_strdup(cmd);
	remove_braces(pa->strip);
	pa->expanded = ft_expansion_dollar(g_sh, pa->strip);
	ft_strdel(&pa->strip);
	*ret = 2;
}

int splitter(char *cmd, t_param *pa, int *ret)
{
	pa->oper = get_operator(cmd, ret);
	if (is_param_exp_char(pa->oper))
		first_split(cmd, pa, ret);
	else if (*ret == -1)
	{
		ft_printf("42sh: %s: bad substitution\n", cmd);
		return (1);
	}
	else
	{
		regular_dollar_expansion(cmd, pa, ret);
		return (1);
	}
	return (0);
}
