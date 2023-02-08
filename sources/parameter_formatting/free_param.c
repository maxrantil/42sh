/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:01:24 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/07 12:25:10 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	free_er(t_param *pa, char **cmd, int i)
{
	ft_strdel(&cmd[i]);
	cmd[i] = ft_strdup(pa->expanded);
	ft_strdel(&pa->expanded);
	ft_strdel(&pa->var);
	ft_strdel(&pa->subs);
	ft_strdel(&pa->strip);
}