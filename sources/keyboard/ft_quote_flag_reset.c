/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_flag_reset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:23:06 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/27 13:31:47 by mbarutel         ###   ########.fr       */
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
	t->bracket = 0;
	if (t->delim)
		ft_strdel(&t->delim);
	while (t->inp[++i])
	{
		if ((t->inp[i] == D_QUO || t->inp[i] == S_QUO) && !t->heredoc)
		{
			if (!special_char_check(t->inp, t->index - 1, '\\'))
				ft_quote_handling(t, t->inp[i]);
		}
		else if (t->inp[i] == '<' && !t->heredoc && !t->quote)
			ft_heredoc_handling(t);
		else if ((t->inp[i] == L_BRAC || t->inp[i] == R_BRAC) && !t->quote)
			ft_bracket_handling(t, i);
	}
}
