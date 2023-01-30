/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:52:21 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/30 19:23:07 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
			if(str[i] == options[j])
				break ;
			j++;
		}
		if (j == opt_count)
			return (i);
		j = 0;
		i++;
	}
	return(0);
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
	while(str[i])
	{
		if (str[i] != c)
			return(0);
		i++;
	}
	return(1);
}

/*
	checks if the flag c is ON (ret 1) or OFF (ret 0) and sets the value on
	session->is_flag_on. returns the number of argument commands
*/

int	check_flag(t_session *session, char **commands, char flag)
{
	int	i;
	int	flag_on;

	flag_on = 0;
	i = 1;
	while (commands[i])
	{
		if (commands[i][0] != '-')
			break;
		if (!str_only_contains_char(commands[i], flag))
			break;
		i++;
	}
	if (i > 1)
		session->is_flag_on = 1;
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
int	validate_cd_options(t_session *session, char **commands)
{
	int		i;
	int		invalid_option;
	int		dash_dash;
	
	i = 1;
	dash_dash = 0;
	while(commands[i][0] == '-')
	{
		if (!commands[i][1])
			return (cd_errors(1));
		if (commands[i][1] && commands[i][1] == '-' && !commands[i][2])
		{
			i++;
			if (commands[i] && commands[i + 1])
				return (cd_errors(1));
			dash_dash = 1;
			break ;
		}
		invalid_option = str_only_contains_chars(commands[i], "LP");
		if (invalid_option != 0)
		{
			print_usage("cd", commands[i][invalid_option]);
			return (1);
		}
		i++;
	}
	if (commands[i - 1 - dash_dash][ft_strlen(commands[i - 1]) - 1] == 'P')
		session->is_flag_on = 1;
	session->option_count = i - 1;
	return (0);
}
