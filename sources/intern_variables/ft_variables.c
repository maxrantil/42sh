/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:54:26 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/23 16:55:34 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	treat_env(t_shell *sh, char **cmd)
{
	sh->temp_env = NULL;
	sh->temp_env_bool = 1;
	sh->temp_env = ft_dup_doublearray(sh->env);
	ft_export(sh, cmd, 1);
}

static void	move_args(char ***cmd, int ret)
{
	int		k;
	int		len;
	char	**new_arr;

	k = 0;
	len = ft_arrlen(&(*cmd)[ret]);
	new_arr = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	while ((*cmd)[ret])
		new_arr[k++] = ft_strdup((*cmd)[ret++]);
	new_arr[k] = NULL;
	ft_arrclean(*cmd);
	*cmd = new_arr;
}

static int	is_changeable(char **cmd, int *ret)
{
	int	i;

	i = 0;
	if (!is_var(cmd[i]))
		return (1);
	while (cmd[i])
	{
		if (is_var(cmd[i]))
			i++;
		else
			break ;
	}
	*ret = i;
	if (cmd[i] != NULL)
		return (i);
	return (0);
}

int	ft_variables(t_shell *sh, char ***cmd)
{
	int		ret;

	ret = 0;
	if (!is_changeable(*cmd, &ret))
		add_var(sh, *cmd);
	else if (ret == 0)
		return (1);
	else if (ret)
		treat_env(sh, *cmd);
	if (!(*cmd)[ret])
		return (0);
	move_args(cmd, ret);
	return (ret);
}
