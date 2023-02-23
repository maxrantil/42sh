/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:54:26 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/23 16:01:30 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	treat_env(t_shell *sh, char *****cmd)
{
	sh->temp_env = NULL;
	sh->temp_env_bool = 1;
	sh->temp_env = ft_dup_doublearray(sh->env);
	ft_export(sh, ***cmd, 1);
}

static void	move_args(char ****cmd, int ret)
{
	int		k;

	k = 0;
	while (k < ret)
		ft_strdel(&(**cmd)[k++]);
	ft_memmove(**cmd, (**cmd)[k], ft_arrlen(&(**cmd)[k]) + 1);
	ft_printf("cmd %s  another cmd k %s\n", ****cmd, (***cmd)[k]);
	// ****cmd = (***cmd)[k];
	// ft_printf("cmd %s  another cmd k %s\n", ****cmd, (***cmd)[k]);
}
// static void	move_args(char *****cmd, int ret)
// {
// 	int		k;

// 	k = 0;
// 	while (k < ret)
// 		ft_strdel(&(***cmd)[k++]);
// 	ft_memmove(****cmd, (***cmd)[k], ft_arrlen((**cmd)[k]) + 1);
// 	ft_printf("cmd %s  another cmd k %s\n", ****cmd, (***cmd)[k]);
// 	// ****cmd = (***cmd)[k];
// 	// ft_printf("cmd %s  another cmd k %s\n", ****cmd, (***cmd)[k]);
// }

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

int	ft_variables(t_shell *sh, char ****cmd)
{
	int		ret;

	ret = 0;
	if (!is_changeable(**cmd, &ret))
		add_var(sh, **cmd);
	else if (ret == 0)
		return (1);
	else if (ret)
		treat_env(sh, &cmd);
	if (!(**cmd)[ret])
		return (0);
	// move_args(&cmd, ret);
	move_args(cmd, ret);
	return (ret);
}
