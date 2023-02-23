/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_heredoc_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:03:33 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/22 16:19:34 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	alias_heredoc_check(char **line)
{
	int	i;
	int	count;

	if (!*line)
		return ;
	i = -1;
	count = 0;
	while ((*line)[++i])
	{
		if ((*line)[i] == '<')
			++count;
		if (count == 2)
		{
			ft_memmove(&(*line)[i], &(*line)[i + 1],
				ft_strlen(&(*line)[i + 1]) + 1);
			--count;
		}
	}
}
