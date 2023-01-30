/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/30 12:17:48 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	hash_error_print(char *arg)
{
	if (arg[0] == '-' && arg[1] != 'r')
	{
		ft_putstr_fd("42sh: hash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("hash: usage: hash [-r] [name ...]\n", 2);
		return (-1);
	}
	else if (arg[0] != '-' && !ft_strnequ(arg, "hash", 4))
	{
		ft_putstr_fd("42sh: hash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not found\n", 2);
		return (-1);
	}
	return (0);
}

void	hash_set(t_shell *sh, char **arg)
{
	int		i;
	int		index;
	char	*exepath;
	t_hash	*tmp;

	i = -1;
	while (arg[++i])
	{
		exepath = search_bin(arg[i], sh->env);
		if (exepath)
		{
			if (!ft_strnequ(arg[i], "hash", 4))
			{
				index = hash_function(arg[i]);
				tmp = sh->ht[index];
				while (tmp && !ft_strequ(arg[i], tmp->program))
					tmp = tmp->next;
				if (tmp == NULL)
					hash_init_struct(sh, exepath, 0);
			}
			ft_strdel(&exepath);
		}
		else
			hash_error_print(arg[i]);
	}
}

int	ft_hash(t_shell *sh, char **arg)
{
	if (ft_strnequ(arg[0], "hash", 4) && !arg[1])
		hash_print(sh->ht);
	else if (ft_strnequ(arg[0], "hash", 4) && ft_strnequ(arg[1], "-r", 2))
		hash_clear(sh->ht);
	hash_set(sh, arg);
	return (0);
}
