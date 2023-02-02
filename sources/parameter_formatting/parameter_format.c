/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:05 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/02 13:42:36 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

static int	check_syntax(char *cmd)
{
	if (ft_strnequ(cmd, "${", 2) && cmd[ft_strlen(cmd) -1] == '}')
		return (1);
	return (0);
}

static char	*remove_braces(char *str)
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

static int	is_legit(char flag)
{
	if (flag == '\0')
		return (0);
	return (flag == ':' || flag == '%' || flag == '#');
}

static char	*get_flag(char *cmd)
{
	int	i;

	i = 2;
	ft_printf("%s\n", &cmd[2]);
	while(ft_isalnum(cmd[i]))
		i++;
	// if (ft_strchr(cmd, ':'))
	// 	return (ft_strchr(cmd, ':'));
	// else if (ft_strchr(cmd, '#'))
	// 	return (ft_strchr(cmd, '#'));
	// else if (ft_strchr(cmd, '%'))
	// 	return (ft_strchr(cmd, '%'));
	return (cmd + i);
}

static void	init_pa(t_param *pa)
{
	pa->list = (char **)ft_memalloc(sizeof(char *) * 100);
	pa->expanded = ft_strnew(1);
	pa->op = 0;
}

static int splits(char **cmd, int i, t_param *pa)
{
	if (pa->flag && is_legit(pa->flag[0]))
	{
		pa->strip = ft_strdup(cmd[i]);
		remove_braces(pa->strip);
		pa->subs = ft_strdup(get_flag(pa->strip + 1));
		pa->op = pa->subs[0];
		pa->subs = \
		(char *)ft_memmove(pa->subs, pa->subs + 1, ft_strlen(pa->subs));
		pa->var = \
		ft_strndup(pa->strip, ft_strlen(pa->strip) - (ft_strlen(pa->subs)));
	}
	else
	{
		pa->expanded = ft_expansion_dollar(g_sh, cmd[i]);
		ft_strdel(&cmd[i]);
		cmd[i] = ft_strdup(pa->expanded);
		return (1);
	}
	return (0);
}

static void	retoken_into_list(t_param *pa)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pa->subs[j])
		pa->list[i++] = retokenize(pa->subs, &j);
}

static int expander(t_param *pa, int ret)
{
	int	i;

	i = -1;
	while (pa->list[++i])
	{
		pa->flag = get_flag(pa->list[i]);
		ft_printf("list [%c]\n", pa->flag[0]);
		if (ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == ':')
			pa->expanded = ft_strupdate(pa->expanded, \
			substitute_or_create(g_sh, pa->list[i], &ret));
		else if ((ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == '#')
			|| (ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == '%'))
			pa->expanded = ft_strupdate(pa->expanded, \
			search_from_var(g_sh, pa->list[i], &ret));
		else
			pa->expanded = ft_strupdate(pa->expanded, pa->list[i]);
		if (ret == -1)
			return (1);
	}
	return (0);
}

static int	joiner(t_param *pa, char *cmd, int ret, int i)
{
	ft_strdel(&pa->subs);
	pa->subs = ft_strjoin(pa->var, pa->expanded);
	pa->flag = get_flag(cmd);
	ft_strdel(&pa->expanded);
	pa->expanded = ft_strnew(1);
	if (pa->flag[0] == ':')
		pa->expanded = ft_strupdate(pa->expanded, \
		substitute_or_create(g_sh, pa->subs, &ret));
	else if (pa->flag[0] == '#' || pa->flag[0] == '%')
		pa->expanded = ft_strupdate(pa->expanded, \
		search_from_var(g_sh, pa->subs, &ret));
	if (!pa->expanded || !*pa->expanded)
	{
		ft_printf("42sh: %s: bad substitution\n", cmd[i]);
		return (-1);
	}
	return (0);
}

static void	free_er(t_param *pa, char **cmd, int i)
{
	ft_strdel(&cmd[i]);
	cmd[i] = ft_strdup(pa->expanded);
	ft_strdel(&pa->var);
	ft_strdel(&pa->subs);
	ft_strdel(&pa->expanded);
	ft_strdel(&pa->strip);
}

int	param_format(char **cmd)
{
	int		i;
	int		ret;
	t_param	pa;

	init_pa(&pa);
	ret = 0;
	i = -1;
	while (cmd[++i])
	{
		if (check_syntax(cmd[i]))
		{
			pa.flag = get_flag(cmd[i]);
			if (splits(cmd, i, &pa))
				break ;
			retoken_into_list(&pa);
			if (expander(&pa, ret))
				return (1);
			if (joiner(&pa, cmd[i], i, ret))
				return (-1);
			free_er(&pa, cmd, i);
		}
	}
	return (0);
}
