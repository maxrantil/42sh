/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:32:53 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 08:52:14 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char *use_default_value(t_shell *sh, char *var, char *subst)
{
	char	*expanded;
	char	**temp;

	temp = (char **)ft_memalloc(sizeof(char *) * 2);
	temp[0] = ft_expansion_dollar(sh, var);
	temp[1] = NULL;
	if (!*temp[0])
		expanded = ft_strdup(subst + 1);
	else
		expanded = ft_strdup(var);
	ft_strdel(&temp[0]);
	ft_strdel(&temp[1]);
	free(temp);
	return (expanded);
}

static char	*assign_default_value(t_shell *sh, char *var, char *subst)
{
	char	*expanded;
	char	**temp;

	temp = (char **)ft_memalloc(sizeof(char *) * 2);
	temp[0] = ft_expansion_dollar(sh, var);
	temp[1] = NULL;
	if (!*temp[0])
	{
		expanded = ft_strdup(subst + 1);
		temp[0] = ft_strjoin(var + 1, subst);
		add_var(sh, temp);
	}
	else
		expanded = ft_strdup(temp[0]);
	ft_strdel(&temp[0]);
	ft_strdel(&temp[1]);
	free(temp);
	return (expanded);
}

static char *display_error(t_shell *sh, char *var, char *subst)
{
	char	*expanded;
	char	**temp;

	temp = (char **)ft_memalloc(sizeof(char *) * 2);
	temp[0] = ft_expansion_dollar(sh, var);
	temp[1] = NULL;
	expanded = NULL;
	if (!*temp[0] && subst[1])
			ft_printf("42sh: %s: %s\n", var + 1, subst + 1);
	else if (!*temp[0] && !subst[1])
		ft_printf("42sh: %s: parameter null or unset\n", var + 1);
	else
		expanded = ft_strdup(temp[0]);
	ft_strdel(&temp[0]);
	ft_strdel(&temp[1]);
	free(temp);
	return (expanded);
}

static char *alternate_value(t_shell *sh, char *var, char *subst)
{
	char	*expanded;
	char	**temp;

	temp = (char **)ft_memalloc(sizeof(char *) * 2);
	temp[0] = ft_expansion_dollar(sh, var);
	temp[1] = NULL;
	expanded = NULL;
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
	ft_strdel(&temp[0]);
	ft_strdel(&temp[1]);
	free(temp);
	return (expanded);
}

char	*get_value(t_shell *sh, char *var, char *subst, int format)
{
	char	*expanded;

	expanded = NULL;
	if (format == USE_DEFAULT)
		expanded = use_default_value(sh, var, subst);
	else if (format == ASSIGN_DEFAULT)
		expanded = assign_default_value(sh, var, subst);
	else if (format == DISPLAY_ERR)
		expanded = display_error(sh, var, subst);
	else if (format == ALTERNATE_VALUE)
		expanded = alternate_value(sh, var, subst);
	return (expanded);
}