/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_variable_validity.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:10:28 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 15:18:56 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	check_var_validity(char *var)
{
	int	i;

	i = 0;
	if (var[i] == '$')
		i++;
	if (var[i] == '{')
		i++;
	if (ft_isalpha(var[i]) || !ft_isalpha(var[i]) && var[i] == '_')
		i++;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '}')
			return (0);
		i++;
	}
	return (1);
}