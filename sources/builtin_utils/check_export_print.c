/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exported.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:26:56 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/15 20:32:04 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	print_exported(t_shell *sh)
{
	char		*value;
	char		*key;
	int			i;
	static int	first;

	i = 0;
	value = NULL;
	while (sh->env[i])
	{
		value = ft_strchr(sh->env[i], '=') + 1;
		key = ft_strndup(sh->env[i], \
		ft_strlen(sh->env[i]) - ft_strlen(value));
		if (ft_strequ(key, "_=") && !first)
		{
			first = 1;
			ft_printf("export %s\"%s\"\n", key, value);
		}
		else if (ft_strequ(key, "_=") && first)
			i++;
		else
			ft_printf("export %s\"%s\"\n", key, value);
		i++;
		ft_strdel(&key);
	}
	return (0);
}

int	check_export_print(t_shell *sh, char **cmd)
{
	if (!cmd[1])
		print_exported(sh);
	else
		return (0);
	return (1);
}
