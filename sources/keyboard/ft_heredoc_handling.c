/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:57:40 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/09 15:59:59 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It checks if the user is
 * currently typing a heredoc, and if so, it sets the `t->heredoc` variable to 1
 *
 * @param t the term structure
 */
void	ft_heredoc_handling(t_term *t)
{
	ssize_t	count;
	ssize_t	start;

	count = 0;
	start = -1;
	while (t->inp[++start] && count <= 2)
	{
		if (t->inp[start] == '<')
			count++;
		else if (t->inp[start] != '<' && count == 2)
			break ;
		else
			count = 0;
	}	
	if (count == 2)
		t->heredoc = 1;
	else
		t->heredoc = 0;
}
