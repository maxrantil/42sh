/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_to_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 09:48:51 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/15 14:20:30 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	add_var_to_list(t_shell *sh, char *var, char *subst)
{
	int	i;

	i = 0;
	while (sh->intr_vars[i])
		i++;
	sh->intr_vars[i] = ft_strjoin(var + 1, subst);
}
