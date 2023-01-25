/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_utils_more.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:38:17 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/12 18:44:40 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	increment_whitespace(char **line)
{
	int	i;

	i = 0;
	while (*line && (*line)[i] && ft_isspace((*line)[i]))
		++i;
	*line += i;
	return (i);
}

int	increment_not_whitespace(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i] && !ft_isspace((*line)[i]))
		++i;
	*line += i;
	return (i);
}

void	print_spaces(int lvl)
{
	int	i;

	i = COUNT;
	while (i++ < lvl)
		ft_printf(" ");
}
