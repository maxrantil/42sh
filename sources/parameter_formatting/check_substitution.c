/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:18:07 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/11 16:55:06 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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

static int	set_values(char *temp, int *ret, t_param *pa)
{
	*ret = -1;
	ft_strdel(&pa->expanded);
	pa->expanded = get_section(temp);
	return (1);
}

int check_substitutions(char *cmd, int *ret, t_param *pa)
{
	int	i;
	int	retu;
	char	*temp;

	i = 0;
	retu = 0;
	while (cmd[i])
	{
		if (ft_strnequ("${", &cmd[i], 2))
		{
			temp = &cmd[i];
			i += 2;
			if (!ft_isalpha(cmd[i]) && cmd[i] != '_' && cmd[i] != '?')
				return (set_values(temp, ret, pa));
			if (cmd[i] == '?')
				return (1);
			i++;
			while (ft_isalnum(cmd[i]))
				i++;
			retu = is_param_exp_char(&cmd[i]);
			if (!retu && cmd[i] != '}')
				return (set_values(temp, ret, pa));
		}
		i++;
	}
	if (!retu && cmd[i - 1] == '}' && ft_isalnum(cmd[i - 2]))
		return (1);
	return (0);
}
