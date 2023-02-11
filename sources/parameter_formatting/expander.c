/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:29:33 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 17:04:01 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell *g_sh;

static int	substitute_value(t_param *pa, int *ret, char *cmd)
{
	char *temp;
	char *subs;

	subs = substitute_or_create(g_sh, cmd, ret);
	temp = ft_strjoin(pa->expanded, subs);
	ft_strdel(&pa->expanded);
	if (!temp || !*temp)
	{
		pa->expanded = ft_strdup(" ");
		ft_strdel(&subs);
		ft_strdel(&temp);
		return (1);
	}
	pa->expanded = ft_strdup(temp);
	ft_strdel(&subs);
	ft_strdel(&temp);
	return (0);
}

static	int	substring_substitution(t_param *pa, int *ret, char *cmd)
{
	char *temp;
	char *subs;

	ft_printf(" eju [%s] \n", cmd);
	subs = search_from_var(g_sh, cmd, ret);
	temp = ft_strjoin(pa->expanded, subs);
	if (!temp)
		return (1);
	ft_strdel(&pa->expanded);
	pa->expanded = ft_strdup(temp);
	ft_strdel(&subs);
	ft_strdel(&temp);
	return (0);
}

int expander(t_param *pa, int ret)
{
	int	i;

	i = -1;
	while (pa->list[++i])
	{
		pa->flag = get_flag(pa->list[i], &ret);
		if (ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == ':')
		{
			if (substitute_value(pa, &ret, pa->list[i]))
				return (1);
		}
		else if ((ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == '#') || (ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == '%'))
		{
			if (substring_substitution(pa, &ret, pa->list[i]))
				return (1);
		}
		else
			pa->expanded = ft_strupdate(pa->expanded, pa->list[i]);
		if (ret == -1 || !*pa->expanded)
			return (1);
	}
	return (0);
}

