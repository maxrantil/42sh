/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:13:43 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/15 20:42:05 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// static void	delete_var(t_shell *sh, int i)
// {
// 	ft_strdel(&sh->intr_vars[i]);
// 	sh->intr_vars[i] = sh->intr_vars[i + 1];
// 	while (sh->intr_vars[i + 1])
// 	{
// 		sh->intr_vars[i] = sh->intr_vars[i + 1];
// 		i++;
// 	}
// 	sh->intr_vars[i] = NULL;
// }

/**
 * It removes the environment variables specified by the user
 *
 * @param sh The session struct.
 * @param cmd The command line arguments.
 *
 * @return The return value is the exit status of the last command executed.
 */
int	ft_unset(t_shell *sh, char **cmd)
{
	int		i;
	int		count;
	char	*ptr;

	i = 0;
	count = 0;
	sh->exit_stat = 0;
	while (*(cmd + (++i)))
	{
		if (ft_env_get(sh, *(cmd + i), sh->env))
		{
			if (ft_strnequ(*(cmd + i), "PATH", 4))
				hash_clear(sh->ht);
			ptr = ft_strjoin(*(cmd + i), "=");
			ft_env_remove(sh, ptr);
			ft_strdel(&ptr);
		}
		else if (ft_var_get(sh, *(cmd + i), &count))
		{
			delete_var(sh, &count);
			count = 0;
		}
	}
	return (0);
}
