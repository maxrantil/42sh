/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_or_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:38:55 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/26 21:15:16 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*remove_braces(char *str)
{
	char	*new;
	int		i;
	int		k;

	k = 0;
	i = 1;
	str[1] = str[2];
	str[ft_strlen(str) - 1] = '\0';
	ft_printf("%s\n", str);
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	ft_printf("%s\n", str);
	new = ft_strdup(str);
	return (new);
}

char	*subst_param(t_shell *sh, char *var, char *subst, int format)
{
	char	*expanded;
	char	**temp;

	expanded = NULL;
	temp = (char **)ft_memalloc(sizeof(char *) * 2);
	temp[0] = ft_expansion_dollar(sh, var);
	ft_printf("temp [%s]\n", temp[0]);
	temp[1] = NULL;
	if (format == 0)
	{
		ft_printf("[%s]\n", temp[0]);
		if (!temp[0])
			expanded = ft_strdup(subst + 1);
		else
			expanded = ft_strdup(var);
		return (expanded);
	}
	else if (format == 1)
	{
		ft_printf("[%s]", var);
		if (!*temp[0])
		{
			expanded = ft_strdup(subst + 1);
			ft_strdel(&temp[0]);
			temp[0] = ft_strjoin(var + 1, subst);
			ft_printf("temp [%s]\n", temp[0]);
			add_var(sh, temp);
			//add_var_to_list(sh, var, subst);
		}
		else
			expanded = ft_strdup(temp[0]);

	}
	else if (format == 2)
	{
		ft_printf("questionmark[%s]\n", var);
		if (!*temp[0] && subst[1])
			ft_printf("42sh: %s: %s\n", var + 1, subst + 1);
		else if (!*temp[0] && !subst[1])
			ft_printf("42sh: %s: parameter null or unset\n", var + 1);
		else
			expanded = ft_strdup(temp[0]);

	}
	else if (format == 3)
	{
		ft_printf("plus sign[%s] %s\n", var, subst);
		if (temp[0][0])
			expanded = ft_strdup(subst);
		else
			expanded = ft_strnew(1);
	}
	ft_printf("expandededed [%s]\n", expanded);
	return (expanded);
}

int	format_mode(char op)
{
	int		format;

	format = -1;
	ft_printf("subst mode %c\n", op);
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

char *substitute_or_create(t_shell *sh, char *cmd)
{
	int		i;
	char	*expanded;
	char	*strip;
	char	*var;
	char	*subs;
	char	op;
	int		format;

	i = -1;
	subs = ft_strnew(1);
	expanded = ft_strnew(1);
	var = ft_strnew(1);
	op = 0;
	format = -1;
	strip = remove_braces(cmd);
	// if (ft_strnequ(cmd, "${#", 3))
	// 		expanded = count_letters(sh, strip);
	ft_printf("sisaantuleva matsku [%s]\n", cmd);
	if (ft_strchr(strip, ':'))
	{
		subs = ft_strdup(ft_strchr(strip, ':') + 1);
		op = subs[0];
		subs = (char *)ft_memmove(subs, subs + 1, ft_strlen(subs));
		var = ft_strndup(strip, ft_strlen(strip) - (ft_strlen(subs) - 1));
	}
	else if (ft_strchr(strip, '#'))
	{
		subs = ft_strdup(ft_strchr(strip, '#'));
		op = subs[0];
	}
	else if (ft_strchr(strip, '%'))
	{
		subs = ft_strdup(ft_strchr(strip, '%'));
		op = subs[0];
	}
	else
	{
		expanded = ft_expansion_dollar(sh, strip);
		if (!expanded)
			expanded = ft_strnew(1);
	}
	ft_printf("expanded asdfasfasfasfd[%s]\n", expanded);
	if (ft_strnequ(subs, "${", 2))
		subs = substitute_or_create(sh, subs);
	
	
	format = format_mode(op);
	if (!*expanded)
		expanded = subst_param(sh, var, subs, format);
	//ft_printf("var [%s] format [%d]\n", var, format);
	ft_printf("expanded [%s]\n", expanded);
	return (expanded);
}
