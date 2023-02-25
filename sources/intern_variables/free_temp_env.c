/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_temp_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:27:17 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/25 12:34:45 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	free_temp_env(t_shell *sh)
{
	if (sh->temp_env_bool)
	{
		ft_free_doublearray(&sh->env);
		sh->env = ft_dup_doublearray(sh->temp_env);
		ft_free_doublearray(&sh->temp_env);
		sh->temp_env_bool = 0;
	}
}
