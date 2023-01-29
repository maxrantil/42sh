/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:52:21 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/25 20:27:29 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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


/*
	we have validated that commands[0] == "cd", and that
	commands[1] and commands[2] exist.
	for 
*/
int	validate_cd_options(t_session *session, char **commands)
{
	(void)session;
	(void)commands;
	return (0);
}
