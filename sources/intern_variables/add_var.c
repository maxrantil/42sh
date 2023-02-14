/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:03:07 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/13 14:36:47 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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


static int find_env(t_shell *sh, char *cmd, int var_len, int *ret)
{
	int	i;

	i = 0;
	while (!*ret && sh->env[i])
	{
		if (ft_strncmp(sh->env[i], cmd, var_len) == 0
			&& sh->env[i][var_len - 1] == '=')
		{

			ft_strdel(&sh->env[i]);
			sh->env[i] = ft_strdup(cmd);
			*ret = 1;
		}
		i++;
	}
	i = 0;
	if (!*ret)
	{
		while(sh->intr_vars[i])
			i++;
		sh->intr_vars[i] = ft_strdup(cmd);
	}
	return (0);
}

int find_var(t_shell *sh, char *cmd, int var_len, int *ret)
{
	int	i;

	i = 0;
	while (sh->intr_vars[i])
	{
		if (ft_strncmp(sh->intr_vars[i], cmd, var_len) == 0
			&& sh->intr_vars[i][var_len - 1] == '=')
		{
			ft_strdel(&sh->intr_vars[i]);
			sh->intr_vars[i] = ft_strdup(cmd);
			*ret += 1;
		}
		i++;
	}
	return (*ret);
}

int add_var(t_shell *sh, char **cmd)
{
	int var_len;
	int	ret;
	int k;

	k = 0;
	while (cmd[k] && is_var(cmd[k]))
	{
		ret = 0;
		var_len = get_var_len(cmd[k]);
		find_var(sh, cmd[k], var_len, &ret);
		find_env(sh, cmd[k], var_len, &ret);
		k++;
	}
	return (k);
}
