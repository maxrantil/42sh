/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:58:22 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/13 20:34:26 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

//	check if alias found in known aliases, return [pos] OR -1
int	check_alias_match(char **aliases, char *cmd)
{
	int		i;
	char	*tmp_cmd;

	if (!cmd || !aliases)
		return (-1);
	i = -1;
	while (aliases[++i])
	{
		tmp_cmd = get_alias_command(aliases[i]);
		if (ft_strequ(tmp_cmd, cmd) == 1)
		{
			ft_strdel(&tmp_cmd);
			return (i);
		}
		ft_strdel(&tmp_cmd);
	}
	return (-1);
}

int	match_first_word(char **alias, char *line)
{
	int		pos;
	char	*first_word;

	if (!line || !alias)
		return (-1);
	first_word = get_first_word(line);
	pos = check_alias_match(alias, first_word);
	ft_strdel(&first_word);
	return (pos);
}
