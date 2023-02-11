/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:19:56 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/11 14:33:40 by mviinika         ###   ########.fr       */
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
	ft_strdel(&pa->strip);
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

static char *get_section(char *cmd)
{
	int	i;
	int	open;
	char	*fresh;

	i = -1;
	open = 0;
	fresh = ft_strnew(ft_strlen(cmd));
	while (cmd[++i])
	{
		if (cmd[i] == '{')
			open += 1;
		else if (cmd[i] == '}')
			open -= 1;
		fresh[i] = cmd[i];
		if (open == 0 && cmd[i] != '$')
			break ;
	}
	return (fresh);
}

static int check_substitutions(char *cmd, int *ret, t_param *pa)
{
	int	i;
	char	*temp;
	//char	*end;

	i = 0;
	while (cmd[i])
	{
		if (ft_strnequ("${", &cmd[i], 2))
		{
			temp = &cmd[i];
			i += 2;
			if (!ft_isalpha(cmd[i]) && cmd[i] != '_')
			{
				*ret = -1;
				//end = ft_strchr(temp, '}');
				
				pa->expanded = get_section(temp);
				return (1);
			}
				
			i++;
			while (ft_isalnum(cmd[i]))
				i++;
			if (!is_param_exp_char(&cmd[i]) && cmd[i] != '}')
			{
				*ret = -1;
				//end = ft_strchr(temp, '}');
				//pa->expanded = ft_strndup(temp, ft_strlen(temp) - ft_strlen(end) + 1);
				pa->expanded = get_section(temp);
				ft_printf("cmd [%s]\n", pa->expanded);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int splitter(char *cmd, t_param *pa, int *ret)
{
	pa->oper = get_operator(cmd, ret);
	if (check_substitutions(cmd, ret, pa) == 0)
		first_split(cmd, pa, ret);
	else if (*ret == -1)
	{
		ft_printf("42sh: %s: bad substitution\n", pa->expanded);
		return (1);
	}
	else
	{
		regular_dollar_expansion(cmd, pa, ret);
		return (1);
	}
	return (0);
}
