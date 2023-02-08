/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:54:18 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/08 18:02:14 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	check_next_conversion(char *alias)
{
	size_t	len;

	if (!alias)
		return (0);
	len = ft_strlen(alias);
	if (len == 0)
		return (1);
	else if (ft_iswhitespace(alias[len - 1]))
		return (1);
	return (0);
}

int	skip_to_second_word(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	while (line[i] && !(ft_iswhitespace(line[i])))
		i++;
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	return (i);
}

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

//	duplicate alias-array without [pos] from original array
void	dup_arr_rm_pos(char **alias, char ***dup_alias, int pos, int size)
{
	*dup_alias = ft_dup_doublearray(alias);
	remove_alias_single(dup_alias, pos, size);
}
