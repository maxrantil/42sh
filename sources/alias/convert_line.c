/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:04:50 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/15 16:06:01 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	**alias_conf(char **alias, char **pre, char **conv, char **post)
{
	*pre = NULL;
	*conv = NULL;
	*post = NULL;
	return (ft_dup_doublearray(alias));
}

static int	skip_cmd_separator(char *line, int i)
{
	while (i >= 0 && is_command_separator(line[i]))
		i--;
	while (i >= 0 && !is_command_separator(line[i]))
		i--;
	return (i);
}

static void	finish_alias_conversion(char ***dup, char **line)
{
	ft_free_doublearray(dup);
	if (!validate_whitespace(*line))
		ft_strdel(line);
	else
		trim_alias_line(line);
}

static char	*save_line_parts(char **pre, char **line, int i, int j)
{
	if (j == -1)
	{
		return (ft_strsub(*line, 0, i + 1));
	}
	else
	{
		*pre = ft_strsub(*line, 0, j + 1);
		return (ft_strsub(*line, j + 1, i - j));
	}
}

void	alias_convert_line(char **line, t_shell *sh)
{
	char	*pre;
	char	*conversion;
	char	*post;
	int		i;
	int		j;

	if (!validate_whitespace(*line))
		return ;
	sh->dup_alias = alias_conf(sh->alias, &pre, &conversion, &post);
	i = ft_strlen(*line) - 1;
	while (i >= 0)
	{
		j = skip_cmd_separator(*line, i);
		if ((*line)[i + 1])
			post = ft_strsub(*line, i + 1, ft_strlen(&(*line)[i + 1]));
		conversion = save_line_parts(&pre, line, i, j);
		convert_alias(&(sh->dup_alias), &conversion, 0);
		check_line_separators(&(sh->dup_alias), &conversion);
		connect_alias_pieces(&pre, &conversion, &post, line);
		free_and_refill_dup_alias(&(sh->dup_alias), sh->alias);
		i = j;
	}
	finish_alias_conversion(&(sh->dup_alias), line);
}
