/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:52:21 by spuustin          #+#    #+#             */
/*   Updated: 2023/02/09 20:05:56 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
	str[0] == '-'
	we chech that str[1] - str[n] only contain chars in OPTIONS
	return 1 for true, 0 for false (bool rather than success)
*/

static int	str_only_contains_chars(char *str, char *options)
{
	int	i;
	int	j;
	int	opt_count;

	i = 1;
	j = 0;
	opt_count = ft_strlen(options);
	while (str[i])
	{
		while (options[j])
		{
			if (str[i] == options[j])
				break ;
			j++;
		}
		if (j == opt_count)
			return (i);
		j = 0;
		i++;
	}
	return (0);
}

/*
	return 1 for true, 0 for false (bool rather than success)
*/

static int	str_only_contains_char(char *str, char c)
{
	int	i;

	i = 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

/*
	checks if the flag c is ON (ret 1) or OFF (ret 0) and sets the value on
	session->is_flag_on. returns the number of argument commands
*/

int	check_flag(t_shell *sh, char **commands, char flag)
{
	int	i;
	// int	flag_on;

	// flag_on = 0;
	i = 1;
	while (commands[i])
	{
		if (commands[i][0] != '-')
			break ;
		if (!str_only_contains_char(commands[i], flag))
			break ;
		i++;
	}
	if (i > 1)
		sh->is_flag_on = 1;
	return (i - 1);
}

int	cd_errors(int mode)
{
	if (mode == 1)
		write(2, "42sh: cd: too many arguments\n", 30);
	return (1);
}

/*
	we have validated that commands[0] == "cd", and that
	commands[1] and commands[2] exist.
	for
*/

int	validate_cd_options(t_shell *sh, char **cmds, int i, int d_dash)
{
	while (cmds[i][0] == '-')
	{
		if (!cmds[i][1])
			return (cd_errors(1));
		if (cmds[i][1] && cmds[i][1] == '-' && !cmds[i][2])
		{
			i++;
			if (cmds[i] && cmds[i + 1])
				return (cd_errors(1));
			d_dash = 1;
			break ;
		}
		if (str_only_contains_chars(cmds[i], "LP") != 0)
		{
			print_usage("cd", cmds[i][str_only_contains_chars(cmds[i], "LP")]);
			return (1);
		}
		i++;
	}
	if (cmds[i - 1 - d_dash][ft_strlen(cmds[i - 1]) - 1] == 'P')
		sh->is_flag_on = 1;
	sh->option_count = i - 1;
	return (0);
}
