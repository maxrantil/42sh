/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:12:50 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/25 15:46:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It prints the environment, or executes a command with a temporary environment
 *
 * @param sh the session struct
 * @param cmd the command line arguments
 *
 * @return The return value of the last command executed.
 */
int	ft_set(t_shell *sh, char ***cmd)
{
	int	i;

	(void)cmd;
	i = -1;
	sh->exit_stat = 0;
	while (*(sh->env + ++i))
		ft_putendl(*(sh->env + i));
	i = -1;
	while (*(sh->intr_vars + ++i))
		ft_putendl(*(sh->intr_vars + i));
	return (0);
}
