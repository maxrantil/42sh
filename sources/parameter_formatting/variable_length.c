/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:36:38 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/11 11:21:44 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell *g_sh;

char *variable_length(char *str)
{
	char *var;
	char *temp;
	int i;
	int k;

	i = 0;
	k = 0;
	var = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		var[k++] = str[i++];
		if (str[i] == '#')
			i++;
	}
	temp = ft_expansion_dollar(g_sh, var);
	i = ft_strlen(temp);
	return (ft_itoa(i));
}
