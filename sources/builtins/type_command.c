/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:32:14 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/29 17:04:04 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
	returns a bool value (1 for yes, 0 for no) on whether a command
	is on a built-in list or not.
*/

static int	is_built_in(char *command)
{
	static char *builtins[6] = {"echo", "cd", "env", "type", "hash", "exit"};
	int			i;

	i = 0;
	while (i < 5)
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

static int	is_hash(t_hash **ht)
{
	int		i;

	i = 0;
	while(i < HASH_SIZE)
	{
		if (ht[i])
			return (1);
		i++;
	}
	return (0);
}

static int	check_invalid_option(char *command)
{
	if (command[0] == '-' && command[1])
	{
		print_usage("type", command[1]);
		return (1);
	}
	return (0);
}

int	type_command(t_session *session, char **commands, char **env)
{
	char	*bin;
	int		i;
	int		is_hashed;

	i = 1;
	if (check_invalid_option(commands[1]) == 1)
		return (0);
	while (commands[i])
	{
		if (!is_built_in(commands[i]))
		{
			is_hashed = is_hash(session->ht);
			bin = search_bin(commands[i], env);
			if (bin)
			{
				if (is_hashed == 1)
					ft_printf("%s is hashed (%s)\n", commands[i], bin);
				else
					ft_printf("%s is %s\n", commands[i], bin);
				session->exit_stat = 0;
			}
			else
			{
				ft_printf("42sh: type: %s: not found\n", commands[i]);
				session->exit_stat = 1;
			}
			ft_memdel((void *)&bin);
		}
		i++;
	}
	return (0);
}
