/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:01:24 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/08 14:24:46 by mbarutel         ###   ########.fr       */
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
