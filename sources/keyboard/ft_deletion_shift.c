/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion_shift.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:37 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/11 16:50:55 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

struct s_p_flags
{
	int	blash;
	int	quote;
	int	heredoc;
	int	bracket;
};

static void	ft_inhibitor_catch(t_term *t, ssize_t index, struct s_p_flags *fl)
{
	fl->blash = 0;
	fl->quote = 0;
	fl->bracket = 0;
	fl->heredoc = 0;
	if (t->inp[index] == '<')
		fl->heredoc = 1;
	else if (t->inp[index] == '\\')
		fl->blash = 1;
	else if ((t->inp[index] == D_QUO || t->inp[index] == S_QUO) \
	&& !special_char_check(t->inp, index, '\\'))
		fl->quote = 1;
	if (t->inp[index] == L_BRAC || t->inp[index] == R_BRAC)
		fl->bracket = 1;
}

/*
 * It deletes a character from the input string and shifts the rest of the
 * string to the left
 *
 * @param t the t_term struct
 * @param mode 0 for backspace, 1 for delete
 */
void	ft_deletion_shift(t_term *t, ssize_t index)
{
	struct s_p_flags	fl[1];

	ft_inhibitor_catch(t, index, fl);
	t->inp[index] = '\0';
	while (&t->inp[index] < &t->inp[t->bytes])
	{
		t->inp[index] = t->inp[index] ^ t->inp[index + 1];
		t->inp[index + 1] = t->inp[index] ^ t->inp[index + 1];
		t->inp[index] = t->inp[index] ^ t->inp[index + 1];
		index++;
	}
	t->bytes--;
	if (fl->blash)
		ft_quote_flag_check(t, t->index);
	else if (fl->heredoc)
	{
		ft_heredoc_handling(t);
		if (!t->heredoc && t->delim)
			ft_strdel(&t->delim);
	}
	else if (fl->quote || fl->bracket)
		ft_quote_flag_reset(t);
}
