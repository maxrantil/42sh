/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:58:13 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/07 16:12:08 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	unalias_error(t_shell *sh, char *str)
{
	ft_putstr_fd("42sh: unalias: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not found\n", 2);
	sh->exit_stat = 1;
}

int	delete_all_alias(t_shell *sh)
{
	ft_free_doublearray(&(sh->alias));
	sh->alias_size = 0;
	sh->alias = ft_create_empty_str_array(0);
	sh->exit_stat = 0;
	return (0);
}

void	remove_alias_single(char ***alias, int rm_pos, int size)
{
	char	**new_arr;
	int		i;
	int		new_pos;

	new_arr = ft_create_empty_str_array(size - 1);
	new_pos = 0;
	i = -1;
	while ((*alias)[++i])
	{
		if (i == rm_pos)
			continue ;
		new_arr[new_pos++] = ft_strdup((*alias)[i]);
	}
	ft_free_doublearray(alias);
	*alias = ft_dup_doublearray(new_arr);
	ft_free_doublearray(&new_arr);
}

void	remove_alias(t_shell *sh, int skip_pos)
{
	char	**new_arr;
	int		i;
	int		new_pos;

	sh->alias_size--;
	new_arr = ft_create_empty_str_array(sh->alias_size);
	new_pos = 0;
	i = -1;
	while (sh->alias[++i])
	{
		if (i == skip_pos)
			continue ;
		new_arr[new_pos++] = ft_strdup(sh->alias[i]);
	}
	ft_free_doublearray(&(sh->alias));
	sh->alias = ft_dup_doublearray(new_arr);
	ft_free_doublearray(&new_arr);
	sh->exit_stat = 0;
}

int	unalias(t_shell *sh, char **args)
{
	int	i;
	int	pos_remove;

	i = 1;
	if (args[i] == NULL)
	{
		ft_printf("unalias: usage: unalias [-a] name [name ...]\n");
		sh->exit_stat = 1;
	}
	else if (ft_strequ(args[i], "-a") == 1)
		return (delete_all_alias(sh));
	while (args[i])
	{
		pos_remove = check_alias_match(sh->alias, args[i]);
		if (pos_remove != -1)
			remove_alias(sh, pos_remove);
		else
			unalias_error(sh, args[i]);
		i++;
	}
	return (0);
}
