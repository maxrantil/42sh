/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_command_update.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:24:16 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/02 15:05:04 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	**get_last_arg(char	**arg)
{
	if (!*arg)
		return (NULL);
	while (*arg)
		arg++;
	return (arg - 1);
}

void	ft_env_last_command(t_shell *sh, char **cmd)
{
	char	*join;
	char	**env;
	char	**last_arg;

	join = NULL;
	env = ft_env_get(sh, "_", sh->env);
	last_arg = get_last_arg(cmd);
	if (last_arg)
	{
		if (env)
		{
			ft_strdel(env);
			*env = ft_strjoin("_=", *last_arg);
		}
		else
		{
			join = ft_strjoin("_=", *last_arg);
			ft_env_append(sh, &join);
			ft_strdel(&join);
		}
	}
}
