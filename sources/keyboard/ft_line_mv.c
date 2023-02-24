/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_mv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:41:49 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/24 13:10:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static ssize_t	delim_row(t_term *t)
{
	ssize_t	delim_row;

	delim_row = 0;
	while (delim_row < t->total_row && (!delim_row \
	|| !ft_is_prompt_line(t, delim_row) \
	|| ft_delim_bslash(t->inp, (t->nl_addr[delim_row] - 2) - t->inp)))
		delim_row++;
	return (delim_row);
}

/*
 * It moves the cursor up or down a line
 *
 * @param t the term structure
 */
void	ft_line_mv(t_term *t)
{
	t->ch = ft_get_input();
	if (t->ch == ';')
	{
		t->ch = ft_get_input();
		if (t->ch == '3')
		{
			t->ch = ft_get_input();
			{
				if (t->ch == ARROW_UP && t->c_row && (!t->heredoc \
				|| t->c_row > delim_row(t)))
					ft_line_up(t);
			}
			if (t->ch == ARROW_DOWN && t->c_row < t->total_row)
				ft_line_down(t);
			t->ch = 0;
		}
	}
}
