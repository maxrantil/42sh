/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:32:14 by spuustin          #+#    #+#             */
/*   Updated: 2023/02/16 15:20:07 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
	returns a bool value (1 for yes, 0 for no) on whether a command
	is on a built-in list or not.
*/

static int	is_built_in(char *command)
{
	static char	*builtins[12] = {"echo", "cd", "env", "type", "hash", "exit",
		"fg", "bg", "jobs", "export", "set", "unset", "alias", "unalias", "fc",
		"history"};
	int			i;

	i = 0;
	while (i < 12)
	{
		if (ft_strequ(builtins[i], command) == 1)
		{
			ft_printf("%s is a shell builtin\n", builtins[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	is_alias(char *command, t_shell *sh)
{
	int		pos;
	char	*content;

	pos = check_alias_match(sh->alias, command);
	if (pos != -1)
	{
		content = get_alias_content_no_quotes(sh->alias[pos]);
		ft_printf("%s is aliased to '%s'\n", command, content);
		ft_strdel(&content);
		return (1);
	}
	return (0);
}

static int	is_hash(t_hash **ht)
{
	int		i;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (ht[i])
			return (1);
		i++;
	}
	return (0);
}

static void	print_bin(char *bin, char *command, t_shell *sh, int is_hashed)
{
	if (bin)
	{
		if (is_hashed == 1)
			ft_printf("%s is hashed (%s)\n", command, bin);
		else
			ft_printf("%s is %s\n", command, bin);
		sh->exit_stat = 0;
	}
	else
	{
		ft_printf("42sh: type: %s: not found\n", command);
		sh->exit_stat = 1;
	}
}

int	type_command(t_shell *sh, char **commands, char **env, int i)
{
	char	*bin;
	int		is_hashed;

	if (!commands[1])
		return (0);
	if (commands[1][0] == '-' && commands[1][1] && commands[2])
	{
		sh->exit_stat = 2;
		print_usage("type", commands[1][1]);
		return (0);
	}
	while (commands[i])
	{
		if (!is_built_in(commands[i]) && !is_alias(commands[i], sh))
		{
			is_hashed = is_hash(sh->ht);
			bin = search_bin(commands[i], env);
			print_bin(bin, commands[i], sh, is_hashed);
			ft_memdel((void *)&bin);
		}
		i++;
	}
	return (0);
}
