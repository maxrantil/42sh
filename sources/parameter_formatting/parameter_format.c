/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:05 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/08 09:39:06 by mviinika         ###   ########.fr       */
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

static int	is_legit(char *flag)
{
	if (*flag == '\0')
		return (0);
	else if (flag[0] == ':')
		return (flag[1] == '-' || flag[1] == '+' || flag[1] == '=' || flag[1] == '?');
	return ((flag[0] == '%'  && flag[1]) || (flag[0] == '#' && flag[1]));
}

// static int	is_legit_format(char *format)
// {
// 	if (format == '\0')
// 		return (0);
// 	return (format == '+' || format == '-' || format == '=');
// }

int check_flag(char flag)
{
	return (flag == '%' || flag == '#' || flag == ':' || flag == '}');
}

static char	*get_operator(char *cmd, int *ret)
{
	int	i;

	i = 2;
	(void)ret;
	//ft_printf("getting operator %s\n",cmd);
	if (!cmd[1])
		return (NULL);
	while (ft_isalnum(cmd[i]))
		i++;
	ft_printf("getting operator %s\n",cmd + i);
	if (!is_legit(&cmd[i]) && cmd[i] != '}')
		*ret = -1;
	return (cmd + i);
}

static char	*get_flag(char *cmd, int *ret)
{
	int	i;

	i = 2;
	(void)ret;
	//ft_printf("getting flag %s\n",cmd);
	if (!cmd[1])
		return (NULL);
	while (ft_isalnum(cmd[i]))
		i++;
	// if (!check_flag(cmd[i]))
	// 	*ret = -1;
	return (cmd + i);
}

static void	init_pa(t_param *pa)
{
	pa->list = (char **)ft_memalloc(sizeof(char *) * 100);
	pa->expanded = ft_strnew(1);
	pa->op = 0;
}

static int splits(char **cmd, int i, t_param *pa, int *ret)
{
	pa->oper = get_operator(cmd[i], ret);
	if (is_legit(pa->oper))
	{
		pa->strip = ft_strdup(cmd[i]);
		remove_braces(pa->strip);
		pa->subs = ft_strdup(get_flag(pa->strip + 1, ret));
		ft_printf("%s\n", pa->subs);
		pa->op = pa->subs[0];
		pa->subs = \
		(char *)ft_memmove(pa->subs, pa->subs + 1, ft_strlen(pa->subs));
		pa->var = \
		ft_strndup(pa->strip, ft_strlen(pa->strip) - (ft_strlen(pa->subs)));
	}
	else if (*ret == -1)
	{
		ft_printf("42sh: %s: bad substitution\n", cmd[i]);
		return (1);
	}
	else
	{
		ft_strdel(&pa->expanded);
		pa->strip = ft_strdup(cmd[i]);
		remove_braces(pa->strip);
		pa->expanded = ft_expansion_dollar(g_sh, pa->strip);
		ft_strdel(&cmd[i]);
		ft_strdel(&pa->strip);
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
	{
		pa->list[i++] = retokenize(pa->subs, &j);
	}
		
}

static int expander(t_param *pa, int ret)
{
	int	i;
	char	*temp;
	char	*subs;

	i = -1;
	while (pa->list[++i])
	{
		pa->flag = get_flag(pa->list[i], &ret);
		// if (!pa->flag)
		// 	pa->expanded = ft_strnew(1);
		//ft_printf("pa list %s  [%c]\n",  pa->list[i], pa->flag[0]);
		if (ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == ':')
		{
			subs = substitute_or_create(g_sh, pa->list[i], &ret);
			temp = ft_strjoin(pa->expanded, subs);
			ft_strdel(&pa->expanded);
			pa->expanded = ft_strdup(temp);
			ft_strdel(&subs);
			ft_strdel(&temp);
		}
		else if ((ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == '#')
			|| (ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == '%'))
		{
			subs = search_from_var(g_sh, pa->list[i], &ret);
			temp = ft_strjoin( pa->expanded, subs);
			ft_strdel(&pa->expanded);
			pa->expanded = ft_strdup(temp);
			ft_printf(" expanded [%s] \n", pa->expanded);
			ft_strdel(&subs);
			ft_strdel(&temp);
		}
		else
			pa->expanded = ft_strupdate(pa->expanded, pa->list[i]);
		if (ret == -1)
			return (1);
	}
	return (0);
}

static int	joiner(t_shell *sh, t_param *pa, char *cmd, int ret)
{
	char	*temp;
	char	*subs;

	ft_strdel(&pa->subs);
	pa->subs = ft_strjoin(pa->var, pa->expanded);
	pa->oper = get_operator(pa->subs, &ret);
	ft_printf("pa list sdfds %s\n", pa->subs);
	ft_printf("pa list  %c\n", pa->oper[0]);
	ft_strdel(&pa->expanded);
	pa->expanded = ft_strnew(1);
	if (pa->oper[0] == ':')
	{
		subs = substitute_or_create(g_sh, pa->subs, &ret);
		temp = ft_strjoin(pa->expanded, subs);
		ft_strdel(&pa->expanded);
		pa->expanded = ft_strdup(temp);
		ft_strdel(&subs);
		ft_strdel(&temp);
		// pa->expanded = ft_strupdate(pa->expanded, 
		// substitute_or_create(g_sh, pa->subs, &ret));
	}
	else if (pa->oper[0] == '#' || pa->oper[0] == '%')
	{
		subs = search_from_var(g_sh, pa->subs, &ret);
		ft_printf(" subs [%s] \n", subs);
		temp = ft_strjoin(pa->expanded, subs);
		ft_strdel(&pa->expanded);
		pa->expanded = ft_strdup(temp);
		ft_printf(" expanded [%s] \n", pa->expanded);
		ft_strdel(&subs);
		ft_strdel(&temp);
		// pa->expanded = ft_strupdate(pa->expanded, 
		// search_from_var(g_sh, pa->subs, &ret));
	}
	else
		pa->expanded = ft_expansion_dollar(sh, cmd);
	if (!pa->expanded || !*pa->expanded)
	{
		pa->expanded = ft_strnew(1);
		//ft_printf("42sh: %s: bad substitution\n", cmd);
		// return (-1);
	}
	if (ret == -1)
	{
		ft_strdel(&pa->expanded);
		ft_printf("42sh: %s: bad substitution\n", cmd);
		return (-1);
	}
	ft_printf("pa list alaalla %s\n", pa->expanded);
	return (0);
}

int	param_format(char **cmd)
{
	int		i;
	int		k;
	int		ret;
	int		err;
	t_param	pa;

	init_pa(&pa);
	ret = 0;
	err = 0;
	i = -1;
	k = 0;
	while (cmd[++i])
	{
		if (check_syntax(cmd[i]))
		{
			if (splits(cmd, i, &pa, &ret) && ret == 0)
			{
				continue ;
			}
			if (ret == 0)
				retoken_into_list(&pa);
			if (ret == 0 && expander(&pa, ret))
				err = 1;
			if (ret == 0 && joiner(g_sh, &pa, cmd[i], ret) && ret == 0)
				err = -1;
			if (ret)
			{
				err = -1;
				break ;
			}
			else
				free_er(&pa, cmd, i);
		}
	}
	while (k < 100)
		ft_strdel(&pa.list[k++]);
	free(pa.list);
	ft_strdel(&pa.expanded);
	return (err);
}
