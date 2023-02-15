/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bracket_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:46:19 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/15 13:37:11 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	ft_bracket_handling(t_term *t, int pos)
{
	if ((t->inp[pos] == L_BRAC \
	&& (!pos || special_char_check(t->inp, pos, '$'))) || t->inp[pos] == R_BRAC)
	{
		if ((!t->bracket || t->bracket == t->inp[pos]) && t->inp[pos] == L_BRAC)
		{
			t->bracket = t->inp[pos];
			++t->bracket_count;
		}
		else if (t->bracket != t->inp[pos])
		{
			--t->bracket_count;
			if (!t->bracket_count)
				t->bracket = 0;
		}
	}
}
