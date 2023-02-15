/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_alias.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:57:03 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/13 21:47:48 by mbarutel         ###   ########.fr       */
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
			ft_putstr_fd("42sh: alias: ", 2);
			ft_putstr_fd_len(alias_name, 2, (size_t)len);
			ft_putstr_fd(" invalid alias name\n", 2);
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

int	validate_whitespace(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (!(ft_iswhitespace(str[i])))
			return (1);
	}
	return (0);
}
