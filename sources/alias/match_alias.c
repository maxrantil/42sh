/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:58:22 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/13 18:22:58 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	print_alias_all1(char **alias)
{
	int	i;

	// sort_aliases(alias);
	i = -1;
	while (alias[++i])
		ft_printf("--\talias %s\n", alias[i]);
}


//	check if alias found in known aliases, return [pos] OR -1
int	check_alias_match(char **aliases, char *cmd)
{
	int		i;
	char	*tmp_cmd;

	if (!cmd || !aliases)
		return (-1);
	i = -1;
	// ft_printf("cmd (%s)\n", cmd);
	// print_alias_all1(aliases);
	// print_alias_all1(aliases);
	while (aliases[++i])
	{
		tmp_cmd = get_alias_command(aliases[i]);
		// ft_printf("\ttmpcmd (%s) i (%d)\n", tmp_cmd, i);
		if (ft_strequ(tmp_cmd, cmd) == 1)
		{
			ft_strdel(&tmp_cmd);
			return (i);
		}
		// ft_printf("\ttmpcmd (%s) i (%d)\n", tmp_cmd, i);
		ft_strdel(&tmp_cmd);
	}
	// ft_printf("cmd END(%s)\n", cmd);
	return (-1);
}

int	match_first_word(char **alias, char *line)
{
	int		pos;
	char	*first_word;

	if (!line || !alias)
		return (-1);
	first_word = get_first_word(line);
	// ft_printf(" ASD first (%s)\n", first_word);
	// ft_printf(" ASD line  (%s)\n", line);
	// print_alias_all1(alias);
	pos = check_alias_match(alias, first_word);
	// ft_printf(" ASD pos  (%d)\n", pos);
	ft_strdel(&first_word);
	return (pos);
}
