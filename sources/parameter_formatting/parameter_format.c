/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:05 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/01 11:17:38 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	check_syntax(char *cmd)
{
	if (ft_strnequ(cmd, "${", 2) && cmd[ft_strlen(cmd) -1] == '}')
		return (1);
	return (0);
}

int	is_in_var_or_env(t_shell *sh, char *var)
{
	int		i;
	int		var_len;
	char	*key;

	i = -1;
	key = ft_strjoin(var, "=");
	var_len = ft_strlen(key);
	while (sh->intr_vars[++i])
	{
		if (ft_strncmp(sh->intr_vars[i], key, var_len) == 0
			&& sh->intr_vars[i][var_len - 1] == '=')
			return (1);
	}
	i = -1;
	while (sh->env[++i])
	{
		if (ft_strncmp(sh->env[i], key, var_len) == 0
			&& sh->env[i][var_len - 1] == '=')
			return (1);
	}
	return (0);
}

static char	*retokenize(t_shell *sh, char *subst, int *i)
{
	char	*trimmed;
	int		k;
	int		j;
	int		open;
	char	*fresh;

	k = 0;
	j = 0;
	open = 0;
	(void)sh;
	trimmed = ft_strtrim(subst);
	fresh = ft_strnew(ft_strlen(subst));
	while (trimmed[*i])
	{
		fresh[k++] = trimmed[(*i)++];
		if (fresh[0] == '$')
		{
			if (trimmed[*i] == '{')
				open += 1;
		}
		if (trimmed[*i] == '}')
		{
			open -= 1;
			if (open == 0)
			{
				fresh[k++] = trimmed[(*i)++];
				break ;
			}
		}
		if (trimmed[*i] == '$' && !open)
			break ;
	}
	ft_strdel(&trimmed);
	return (fresh);
}

char	*count_letters(t_shell *sh, char *cmd)
{
	int		i;
	int		k;
	char	*expanded;
	char	*var;

	i = 0;
	k = 0;
	expanded = NULL;
	var = ft_strnew(ft_strlen(cmd));
	while (cmd[i])
	{
		if (cmd[i] == '#')
			i++;
		var[k++] = cmd[i++];
	}
	i = 1;
	expanded = ft_expansion_dollar(sh, var);
	ft_strdel(&var);
	return (ft_itoa(ft_strlen(expanded)));
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
	if (ft_strchr(cmd, ':'))
		return (ft_strchr(cmd, ':'));
	else if (ft_strchr(cmd, '#'))
		return (ft_strchr(cmd, '#'));
	else if (ft_strchr(cmd, '%'))
		return (ft_strchr(cmd, '%'));
	return (NULL);
}

static void	init_pa(t_param *pa)
{
	pa->list = (char **)ft_memalloc(sizeof(char *) * 100);
	pa->expanded = ft_strnew(1);
	pa->var = NULL;
	pa->flag = NULL;
	pa->strip = NULL;
	pa->list = NULL;
	pa->op = 0;
}



int	param_format(t_shell *sh, char **cmd)
{
	int		i;
	int		k;
	int		j;
	int		ret;
	t_param	pa;

	init_pa(&pa);
	ret = 0;
	j = 0;
	k = 0;
	i = -1;
	while (cmd[++i])
	{
		if (check_syntax(cmd[i]))
		{
			pa.flag = get_flag(cmd[i]);
			if (pa.flag && is_legit(pa.flag[0]))
			{
				pa.strip = ft_strdup(cmd[i]);
				remove_braces(pa.strip);
				pa.subs = ft_strdup(get_flag(pa.strip + 1));
				pa.op = pa.subs[0];
				pa.subs = (char *)ft_memmove(pa.subs, pa.subs + 1, ft_strlen(pa.subs));
				pa.var = ft_strndup(pa.strip, ft_strlen(pa.strip) - (ft_strlen(pa.subs)));
			}
			else
			{
				pa.expanded = ft_expansion_dollar(sh, cmd[i]);
				ft_strdel(&cmd[i]);
				cmd[i] = ft_strdup(pa.expanded);
				break ;
			}
			while (pa.subs[j])
				pa.list[k++] = retokenize(sh, pa.subs, &j);
			k = 0;
			while (pa.list[k])
			{
				if (ft_strnequ(pa.list[k], "${", 2))
					pa.expanded = ft_strupdate(pa.expanded, substitute_or_create(sh, pa.list[k++], &ret));
				else
					pa.expanded = ft_strupdate(pa.expanded, pa.list[k++]);
				if (ret == -1)
					return (1);
			}
			ft_strdel(&pa.subs);
			pa.subs = ft_strjoin(pa.var, pa.expanded);
			ft_strdel(&pa.expanded);
			pa.expanded = substitute_or_create(sh, pa.subs, &ret);
			if (!pa.expanded || !*pa.expanded)
			{
				ft_printf("42sh: %s: bad substitution\n", cmd[i]);
				return (-1);
			}
			ft_strdel(&cmd[i]);
			cmd[i] = ft_strdup(pa.expanded);
			ft_strdel(&pa.var);
			ft_strdel(&pa.subs);
			ft_strdel(&pa.expanded);
			ft_strdel(&pa.strip);

		}
	}
	return (0);
}
