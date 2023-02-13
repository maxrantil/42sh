/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:13:00 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/11 15:48:49 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char *get_operator(char *cmd)
{
	int i;

	i = 2;
	if (!cmd[1])
		return (NULL);
	while (ft_isalnum(cmd[i]))
		i++;
	return (cmd + i);
}
