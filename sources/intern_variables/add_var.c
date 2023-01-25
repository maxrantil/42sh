/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:03:07 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/25 15:32:04 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	get_var_len(char *input)
{
	int	i;
	int	var_len;

	i = -1;
	var_len = 0;
	while (input[++i])
	{
		var_len++;
		if (input[i] == '=')
			break ;
	}
	return (var_len);
}


static int find_env(t_session *sesh, char *cmd, int var_len, int *ret)
{
	int	i;

	i = 0;
	while (!*ret && sesh->env[i])
	{
		if (ft_strncmp(sesh->env[i], cmd, var_len) == 0
			&& sesh->env[i][var_len - 1] == '=')
		{

			ft_strdel(&sesh->env[i]);
			sesh->env[i] = ft_strdup(cmd);
			*ret = 1;
		}
		i++;
	}
	i = 0;
	if (!*ret)
	{
		while(sesh->intr_vars[i])
			i++;
		sesh->intr_vars[i] = ft_strdup(cmd);
	}
	return (0);
}

int find_var(t_session *sesh, char *cmd, int var_len, int *ret)
{
	int	i;

	i = 0;
	while (sesh->intr_vars[i])
	{
		ft_printf("var [%s] %c\n", sesh->intr_vars[i], sesh->intr_vars[i][var_len - 1]);
		if (ft_strncmp(sesh->intr_vars[i], cmd, var_len) == 0
			&& sesh->intr_vars[i][var_len - 1] == '=')
		{
			ft_strdel(&sesh->intr_vars[i]);
			sesh->intr_vars[i] = ft_strdup(cmd);
			*ret += 1;
		}
		i++;
	}
	return (*ret);
}

int add_var(t_session *sesh, char **cmd)
{
	int var_len;
	int	ret;
	int k;
	int	i;

	k = 0;
	i = 0;
	ft_printf("add var%s\n", cmd[0]);
	while (cmd[k] && is_var(cmd[k]))
	{
		ret = 0;
		var_len = get_var_len(cmd[k]);
		find_var(sesh, cmd[k], var_len, &ret);
		find_env(sesh, cmd[k], var_len, &ret);
		i = 0;
		k++;
	}
	return (k);
}
