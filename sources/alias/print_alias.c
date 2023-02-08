/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:03:05 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/08 18:20:38 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	alias_error(char *str)
{
	ft_putstr_fd("42sh: alias: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not found\n", 2);
}

void	sort_aliases(char **alias)
{
	int		i;
	char	*tmp;

	i = 0;
	while (alias[i] && alias[i + 1])
	{
		if (ft_strcmp(alias[i], alias[i + 1]) > 0)
		{
			tmp = alias[i];
			alias[i] = alias[i + 1];
			alias[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

int	print_alias_single(char *cmd, char **aliases)
{
	int	pos;

	pos = check_alias_match(aliases, cmd);
	if (pos != -1)
	{
		ft_printf("alias %s\n", aliases[pos]);
		return (0);
	}
	else
	{
		alias_error(cmd);
		return (1);
	}
}

void	print_alias_all(char **alias, t_shell *sh)
{
	int	i;

	sort_aliases(alias);
	i = -1;
	while (alias[++i])
		ft_printf("alias %s\n", alias[i]);
	sh->exit_stat = 0;
}
