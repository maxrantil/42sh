/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_or_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:38:55 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 08:49:19 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	format_mode(char op)
{
	int		format;

	format = -1;
	if (op == '-')
		format = USE_DEFAULT;
	else if (op == '=')
		format = ASSIGN_DEFAULT;
	else if (op == '?')
		format = DISPLAY_ERR;
	else if (op == '+')
		format = ALTERNATE_VALUE;
	return (format);
}

void set_sub_var_op(t_param *param)
{
	ft_strdel(&param->subs);
	//param->var = NULL;
	ft_strdel(&param->var);
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
	param.var = ft_strnew(1);
	param.op = 0;
	format = -1;
	param.strip = ft_strdup(cmd);
	param.strip = remove_braces(param.strip);
	ft_printf("param.strip %s\n", param.strip);
	if (ft_strchr(param.strip, ':'))
		set_sub_var_op(&param);
	else
	{
		param.expanded = ft_expansion_dollar(sh, param.strip);
		if (!param.expanded || !*param.expanded)
		{
			ft_strdel(&param.subs);
			ft_strdel(&param.strip);
			ft_strdel(&param.var);
			ft_strdel(&param.expanded);
			param.expanded = ft_strnew(1);
			return(param.expanded);
		}
	}
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
	ft_printf("subs %s\n",  param.subs);
	if (!param.expanded || !*param.expanded)
		param.expanded = get_value(sh, param.var, param.subs, format);
	// if (*param.expanded == '$')
	// 	param.expanded = ft_strnew(1);
	//ft_printf("expanded %s\n",  param.expanded);
	ft_strdel(&param.subs);
	ft_strdel(&param.var);
	ft_strdel(&param.strip);
	return (param.expanded);
}
