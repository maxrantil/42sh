/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:40:55 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 13:23:38 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char *get_flag(char *cmd, int *ret)
{
	int i;

	i = 2;
	(void)ret;
	// ft_printf("getting flag %s\n",cmd);
	if (!cmd[1])
		return (NULL);
	while (ft_isalnum(cmd[i]))
		i++;
	// if (!check_flag(cmd[i]))
	// 	*ret = -1;
	return (cmd + i);
}