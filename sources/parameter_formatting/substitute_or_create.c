/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_or_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:38:55 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/23 22:00:36 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	split_param(t_param *param)
{
	ft_strdel(&param->subs);
	ft_strdel(&param->var);
	param->subs = ft_strdup(ft_strchr(param->strip, ':'));
	param->subs = \
	(char *)ft_memmove(param->subs, param->subs + 1, ft_strlen(param->subs));
	param->op = param->subs[0];
	param->var = \
	ft_strndup(param->strip, ft_strlen(param->strip) \
	- (ft_strlen(param->subs) + 1));
	return (0);
}

static void	init_param(t_param *param, char *cmd)
{
	param->subs = ft_strnew(1);
	param->expanded = NULL;
	param->var = ft_strnew(1);
	param->op = 0;
	param->strip = ft_strdup(cmd);
	param->strip = remove_braces(param->strip);
}

static void	del_param(t_param *param, int opt)
{
	ft_strdel(&param->subs);
	ft_strdel(&param->strip);
	ft_strdel(&param->var);
	if (opt)
		ft_strdel(&param->expanded);
}

static char	*get_temp_subst(t_param *param, t_shell *sh, int *ret)
{
	char	*subs;

	subs = NULL;
	if ((ft_strnequ(param->subs + 1, "${", 2) && ft_strchr(param->subs, '#'))
		|| (ft_strnequ(param->subs + 1, "${", 2)
			&& ft_strchr(param->subs, '%')))
		subs = search_from_var(sh, param->subs + 1, ret);
	else if (ft_strnequ(param->subs + 1, "${", 2))
		subs = substitute_or_create(sh, param->subs + 1, ret);
	if (subs)
	{
		ft_strdel(&param->subs);
		param->subs = ft_strdup(subs);
		ft_strdel(&subs);
	}
	return (subs);
}

char	*substitute_or_create(t_shell *sh, char *cmd, int *ret)
{
	t_param	param;
	int		format;

	format = -1;
	init_param(&param, cmd);
	if (ft_strchr(param.strip, ':'))
		split_param(&param);
	else
	{
		param.expanded = ft_expansion_dollar(sh, param.strip);
		if (!param.expanded || !*param.expanded)
		{
			del_param(&param, 1);
			param.expanded = ft_strnew(1);
			return (param.expanded);
		}
	}
	get_temp_subst(&param, sh, ret);
	format = format_mode(param.op);
	if (!param.expanded || !*param.expanded)
		param.expanded = get_value(sh, param.var, param.subs, &format);
	if (format == -2)
		*ret = -2;
	del_param(&param, 0);
	return (param.expanded);
}
