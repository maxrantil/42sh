/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:18:07 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/13 13:14:21 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*get_section(char *cmd)
{
	int		i;
	int		open;
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

static int	set_values(char *temp, int *ret, t_param *pa)
{
	*ret = -1;
	ft_strdel(&pa->expanded);
	pa->expanded = get_section(temp);
	return (1);
}

static char *get_subs(char *cmd)
{
	char	*subs;

	if (ft_strchr(cmd, ':'))
		subs = ft_strchr(cmd, ':');
	else if (ft_strchr(cmd, '#'))
		subs = ft_strchr(cmd, '#');
	else if (ft_strchr(cmd, '%'))
		subs = ft_strchr(cmd, '%');
	else 
		subs = NULL;
	return (subs);
}

static int	check_variable(int *i, char *cmd, int *ret, t_param *pa)
{
	char	*temp;
	int		retu;
	int		k;

	temp = &cmd[*i];
	(*i) += 2;
	if (!get_subs(cmd))
		return (1);
	k = -1;
	if (!ft_isalpha(cmd[*i]) && cmd[*i] != '_' && cmd[*i] != '?')
		return (set_values(temp, ret, pa));
	if (cmd[*i] == '?')
		return (1);
	(*i)++;
	while (ft_isalnum(cmd[*i]))
		(*i)++;
	retu = is_param_exp_char(&cmd[*i]);
	if (!retu && cmd[*i] != '}')
		return (set_values(temp, ret, pa));
	return (0);
}

int	check_substitutions(char *cmd, int *ret, t_param *pa)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strnequ("${", &cmd[i], 2))
		{
			if (check_variable(&i, cmd, ret, pa))
				return (1);
		}
		i++;
	}
	return (0);
}
