/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:13:00 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 13:23:05 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char *get_operator(char *cmd, int *ret)
{
	int i;

	i = 2;
	(void)ret;
	// ft_printf("getting operator %s\n",cmd);
	if (!cmd[1])
		return (NULL);
	while (ft_isalnum(cmd[i]))
		i++;
	// ft_printf("getting operator %s\n",cmd + i);
	if (!is_param_exp_char(&cmd[i]) && cmd[i] != '}')
		*ret = -1;
	return (cmd + i);
}
