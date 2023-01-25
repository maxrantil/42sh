/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_flag_reset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:23:06 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/17 12:55:20 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It resets the flags that are used to determine if the user is in a quote
 * or a heredoc
 * 
 * @param t the structure containing all the information about the current line
 */
void	ft_quote_flag_reset(t_term *t)
{
	ssize_t	i;

	i = -1;
	t->q_qty = 0;
	t->quote = 0;
	t->heredoc = 0;
	if (t->delim)
		ft_strdel(&t->delim);
	while (t->inp[++i])
	{
		if ((t->inp[i] == D_QUO || t->inp[i] == S_QUO) && !t->heredoc)
		{
			if (!ft_bslash_escape_check(t, i))
				ft_quote_handling(t, t->inp[i]);
		}
		if (t->inp[i] == '<' && !t->quote)
			ft_heredoc_handling(t);
	}
}
