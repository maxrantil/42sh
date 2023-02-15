/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_separators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:27:01 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/15 16:29:21 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	init_line_separators(char **pre, char **conv, int *i)
{
	*pre = NULL;
	*conv = NULL;
	*i = -1;
}

static void	del_line_parts(char **pre, char **conv)
{
	if (*pre)
		ft_strdel(pre);
	ft_strdel(conv);
}

int	is_command_separator(char command)
{
	if (command == '|' || command == ';' || command == '&' )
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void	check_line_separators(char ***alias, char **line)
{
	int		i;
	char	*pre_semicolon;
	char	*conversion;

	init_line_separators(&pre_semicolon, &conversion, &i);
	while ((*line)[++i])
	{
		if (is_command_separator((*line)[i]))
		{
			while ((*line)[i] && is_command_separator((*line)[i]))
				i++;
			if (!(*line)[i])
				return ;
			if (i > 0)
				pre_semicolon = ft_strsub(*line, 0, i + 1);
			conversion = ft_strsub(*line, i, ft_strlen(&(*line)[i]));
			if (convert_alias(alias, &conversion, 0))
			{
				ft_strdel(line);
				*line = ft_strjoin_three(pre_semicolon, "", conversion);
				i--;
			}
			del_line_parts(&pre_semicolon, &conversion);
		}
	}
}
