/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_or_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:38:55 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/07 15:45:05 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*subst_param(t_shell *sh, char *var, char *subst, int format)
{
	char	*expanded;
	char	**temp;

	expanded = NULL;
	temp = (char **)ft_memalloc(sizeof(char *) * 2);
	temp[0] = ft_expansion_dollar(sh, var);
	temp[1] = NULL;
	if (format == 0)
	{
		ft_strdel(&expanded);
		if (!temp[0])
			expanded = ft_strdup(subst + 1);
		else
			expanded = ft_strdup(var);
		return (expanded);
	}
	else if (format == 1)
	{
		ft_strdel(&expanded);
		if (!*temp[0])
		{
			expanded = ft_strdup(subst + 1);
			temp[0] = ft_strjoin(var + 1, subst);
			add_var(sh, temp);
		}
		else
			expanded = ft_strdup(temp[0]);
	}
	else if (format == 2)
	{
		ft_strdel(&expanded);
		if (!*temp[0] && subst[1])
			ft_printf("42sh: %s: %s\n", var + 1, subst + 1);
		else if (!*temp[0] && !subst[1])
			ft_printf("42sh: %s: parameter null or unset\n", var + 1);
		else
			expanded = ft_strdup(temp[0]);
	}
	else if (format == 3)
	{
		if (temp[0][0])
		{
			if (subst && *subst)
			{
				if (subst[0] == '+')
					expanded = ft_strdup(subst + 1);
				else
					expanded = ft_strdup(subst);
			}
		}
	}
	ft_strdel(&temp[0]);
	ft_strdel(&temp[1]);
	free(temp);
	ft_strdel(&var);
	return (expanded);
}

int	format_mode(char op)
{
	int		format;

	format = -1;
	if (op == '-')
		format = 0;
	else if (op == '=')
		format = 1;
	else if (op == '?')
		format = 2;
	else if (op == '+')
		format = 3;
	return (format);
}

void set_sub_var_op(t_param *param)
{
	ft_strdel(&param->subs);
	//param->var = NULL;
	//ft_strdel(&param->var);
	param->subs = ft_strdup(ft_strchr(param->strip, ':'));
	param->subs = (char *)ft_memmove(param->subs, param->subs + 1, ft_strlen(param->subs));
	param->op = param->subs[0];
	param->var = ft_strndup(param->strip, ft_strlen(param->strip) - (ft_strlen(param->subs)) - 1);
}

char *substitute_or_create(t_shell *sh, char *cmd, int *ret)
{
	t_param	param;
	int		format;
	char	*subs;

	param.subs = ft_strnew(1);
	subs = NULL;
	param.expanded = NULL;
	//param.var = ft_strnew(1);
	param.op = 0;
	format = -1;
	param.strip = ft_strdup(cmd);
	param.strip = remove_braces(param.strip);
	if (ft_strchr(param.strip, ':'))
		set_sub_var_op(&param);
	else
		param.expanded = ft_expansion_dollar(sh, param.strip);
	// if (ft_strnequ(param.subs + 1, "${", 2) && ft_strchr(param.subs , ':'))
	// 	param.subs = substitute_or_create(sh, param.subs + 1, ret);
	if ((ft_strnequ(param.subs + 1, "${", 2) && ft_strchr(param.subs , '#'))
		|| (ft_strnequ(param.subs + 1, "${", 2) && ft_strchr(param.subs , '%')))
		subs = search_from_var(sh, param.subs + 1, ret);
	else if (ft_strnequ(param.subs + 1, "${", 2))
		subs = substitute_or_create(sh, param.subs + 1, ret);
	format = format_mode(param.op);
	if (subs)
	{
		ft_strdel(&param.subs);
		param.subs = ft_strdup(subs);
		ft_strdel(&subs);
	}
	if (!param.expanded || !*param.expanded)
		param.expanded = subst_param(sh, param.var, param.subs, format);
	ft_strdel(&param.subs);
	ft_strdel(&param.strip);
	return (param.expanded);
}
