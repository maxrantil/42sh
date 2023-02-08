/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_alias.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:57:03 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/08 17:50:48 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	validate_alias_name_print(char *alias_name, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (alias_name[i] == '$' || alias_name[i] == '/'
			|| alias_name[i] == '`')
		{
			write(2, "42sh: alias: ", 13);
			write(2, alias_name, (size_t)len);
			write(2, " invalid alias name\n", 20);
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_alias_name(char *alias_name, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (alias_name[i] == '$' || alias_name[i] == '/'
			|| alias_name[i] == '`')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_alias(char *alias, int print_error)
{
	int	i;
	int	j;

	if (ft_strcount(alias, '=') < 1)
		return (0);
	i = 0;
	while (ft_iswhitespace(alias[i]))
		i++;
	j = i;
	while (alias[i] && alias[i] != '=')
		i++;
	if (i == j)
		return (0);							// nothing before '='
	if (print_error == 1)
		return (1);
	else if (print_error == 2)
		return (validate_alias_name_print(&alias[j], i));
	else
		return (validate_alias_name(&alias[j], i));
}
