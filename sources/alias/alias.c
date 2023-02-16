/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:09:58 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/14 22:46:53 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*construct_alias(char *cmd)
{
	char	*alias;
	char	*command;
	char	*content;

	content = get_alias_content(cmd);
	command = get_alias_command(cmd);
	add_quotes(&content);
	alias = ft_strjoin_three(command, "=", content);
	ft_strdel(&command);
	ft_strdel(&content);
	return (alias);
}

static void	add_alias(t_shell *sh, char *cmd)
{
	char	**new_alias_arr;
	char	*new_alias;
	char	*new_cmd;
	int		found_pos;

	new_alias = construct_alias(cmd);
	new_cmd = get_alias_command(new_alias);
	found_pos = check_alias_match(sh->alias, new_cmd);
	if (found_pos != -1)
	{
		ft_strdel(&(sh->alias[found_pos]));
		sh->alias[found_pos] = ft_strdup(new_alias);
	}
	else
	{
		sh->alias_size++;
		new_alias_arr = ft_create_empty_str_array(sh->alias_size);
		ft_copy_doublearray(sh->alias, new_alias_arr);
		new_alias_arr[sh->alias_size - 1] = ft_strdup(new_alias);
		ft_free_doublearray(&(sh->alias));
		sh->alias = new_alias_arr;
	}
	ft_strdel(&new_alias);
	ft_strdel(&new_cmd);
	sh->exit_stat = 0;
}

static void	add_or_print_alias(char **args, t_shell *sh)
{
	int	i;

	i = 0;
	if (ft_strequ(args[1], "-p") == 1)
	{
		print_alias_all(sh->alias, sh);
		i++;
	}
	while (args[++i])
	{
		if (validate_alias(args[i], 1))
		{
			if (validate_alias(args[i], 2))
				add_alias(sh, args[i]);
			else
				sh->exit_stat = 1;
		}
		else
			sh->exit_stat = print_alias_single(args[i], sh->alias);
	}
}

int	alias(t_shell *sh, char **args)
{
	if (args[1])
	{
		add_or_print_alias(args, sh);
	}
	else
	{
		print_alias_all(sh->alias, sh);
	}
	return (0);
}
