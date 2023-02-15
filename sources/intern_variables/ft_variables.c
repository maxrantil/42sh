/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:54:26 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/14 21:17:54 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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
	int		k;
	char	*temp;

	k = 0;
	ret = 0;
	if (!is_changeable(**cmd, &ret))
		add_var(sh, **cmd);
	else if (ret == 0)
		return (1);
	if (!(**cmd)[ret])
		return (0);
	while ((**cmd)[k + 1])
	{
		ft_strdel(&(**cmd)[k]);
		temp = (**cmd)[k + 1];
		(**cmd)[k] = ft_strdup(temp);
		k++;
	}
	ft_strdel(&(**cmd)[k]);
	return (ret);
}
