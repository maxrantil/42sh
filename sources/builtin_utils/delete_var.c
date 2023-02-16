/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:34:43 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/15 20:44:37 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	delete_var(t_shell *sh, int *i)
{
	ft_strdel(&sh->intr_vars[*i]);
	sh->intr_vars[*i] = sh->intr_vars[*i + 1];
	while (sh->intr_vars[*i + 1])
	{
		sh->intr_vars[*i] = sh->intr_vars[*i + 1];
		*i += 1;
	}
	sh->intr_vars[*i] = NULL;
}
