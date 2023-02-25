/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_heredoc_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:03:33 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/25 15:33:04 by jniemine         ###   ########.fr       */
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
		if ((*line)[i] == '<' && (*line)[i + 1] == '<')
			++count;
		if (count == 1)
		{
			ft_memmove(&(*line)[i], &(*line)[i + 1],
				ft_strlen(&(*line)[i + 1]) + 1);
			--count;
		}
	}
}
