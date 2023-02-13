/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_subs_session.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:21:59 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/11 11:20:49 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void init_subs_session(t_sub *sub, char *cmd)
{
	sub->expanded = NULL;
	sub->needle = NULL;
	sub->haystack = NULL;
	ft_memset(sub->op, '\0', 3);
	sub->strip = ft_strdup(cmd);
	remove_braces(sub->strip);
	sub->temp_hays = NULL;
	sub->temp_sub = NULL;
}
