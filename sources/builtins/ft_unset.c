/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:13:43 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/16 15:15:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	delete_var(t_session *sesh, int i)
{
	ft_strdel(&sesh->intr_vars[i]);
	sesh->intr_vars[i] = sesh->intr_vars[i + 1];
	while (sesh->intr_vars[i + 1])
	{
		sesh->intr_vars[i] = sesh->intr_vars[i + 1];
		i++;
	}
	sesh->intr_vars[i] = NULL;
}

/**
 * It removes the environment variables specified by the user
 * 
 * @param sesh The session struct.
 * @param cmd The command line arguments.
 * 
 * @return The return value is the exit status of the last command executed.
 */
int	ft_unset(t_session *sesh, char **cmd)
{
	int		i;
	int		count;
	char	*ptr;

	i = 0;
	count = 0;
	sesh->exit_stat = 0;
	while (*(cmd + (++i)))
	{
		if (ft_env_get(sesh, *(cmd + i)))
		{
			ptr = ft_strjoin(*(cmd + i), "=");
			ft_env_remove(sesh, ptr);
			ft_strdel(&ptr);
		}
		else if (ft_var_get(sesh, *(cmd + i), &count))
		{
			delete_var(sesh, count);
			count = 0;
		}
	}
	return (0);
}
