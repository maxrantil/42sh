/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:09:58 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/09 13:58:05 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

//	TMP
char	*construct_alias(char *cmd, t_shell *sh)
{
	(void)sh;

	if (cmd)
		return (cmd);
	else
		return (NULL);
}

// char	*construct_alias(char *cmd, t_shell *sh)
// {
// 	int		i;
// 	char	*added_quotes;		// comment tmp
// 	char	*command;
// 	char	*content;

// 	if (cmd)
// 		return (cmd);

// 	i = 0;
// 	while (cmd[i] && cmd[i] != '=')
// 		i++;

// 	convert_dollar_tilde(cmd, i, sh);

// 	if (cmd[i + 1] && cmd[i + 1] == '\"')
// 	{
// 		/*
// 			c="clear"
// 		->	c='clear'
// 		*/

// 		// convert ~ && $
// 		strip_quotes_single(cmd, i + 1);
// 	}
// 	else if (cmd[i + 1] && cmd[i + 1] != '\'')
// 	{
// 		/*
// 			c=clear
// 		->	c='clear'
// 		*/
// 		strip_quotes_single(cmd, i + 1);
// 	}

// 	content = get_alias_content(cmd);
// 	command = get_alias_command(cmd);

// 	added_quotes = ft_strjoin_three("\'", cmd, "\'");
// 	return (NULL);
// }

void	add_alias(t_shell *sh, char *cmd)
{
	char	**new_alias_arr;
	char	*new_alias;
	char	*new_cmd;
	int		found_pos;

	new_alias = construct_alias(cmd, sh);
	new_cmd = get_alias_command(cmd);
	// new_cmd = get_alias_command(new_alias);

	found_pos = check_alias_match(sh->alias, new_cmd);
	if (found_pos != -1)	// already found, replace
	{
		ft_strdel(&(sh->alias[found_pos]));
		sh->alias[found_pos] = ft_strdup(new_alias);
		// ft_strdel(&new_alias);
	}
	else 					// not found in known aliases, add
	{
		sh->alias_size++;
		new_alias_arr = ft_create_empty_str_array(sh->alias_size);
		ft_copy_doublearray(sh->alias, new_alias_arr);
		new_alias_arr[sh->alias_size - 1] = ft_strdup(new_alias);
		ft_free_doublearray(&(sh->alias));
		sh->alias = new_alias_arr;
	}
	ft_strdel(&new_cmd);
	sh->exit_stat = 0;
}

void	add_or_print_alias(char **args, t_shell *sh)
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
