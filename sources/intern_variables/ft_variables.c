/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:54:26 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/14 16:45:30 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int ft_variables(t_shell *sh, char ****cmd)
{
	int ret;
	int	k;
	int	i;
	char	**new_cmd;

	k = 0;
	ret = 0;
	i = 0;
	
	if (is_var(***cmd))
		ret = add_var(sh, **cmd);
	else
		return (0);
	new_cmd = (char **)ft_memalloc(sizeof(char *) * 100);
	while ((**cmd)[k + ret])
	{
		new_cmd[i++] = ft_strdup((**cmd)[k + ret]);
		k++;
	}
	k = 0;
	while ((**cmd)[k])
		ft_strdel(&(**cmd)[k++]);
	free(**cmd);
	new_cmd[i] = NULL;
	**cmd = new_cmd;
	return (ret);
}
