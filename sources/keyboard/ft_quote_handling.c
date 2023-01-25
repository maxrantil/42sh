/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:23:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 17:14:19 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * If the quote character is not set, set it to the character passed in.
 * If the quote character is set, and the character passed in is the same as
 * the quote character, unset the quote character
 *
 * @param t the term structure
 * @param ch the character that was just typed
 */
void	ft_quote_handling(t_term *t, char ch)
{
	if (!t->q_qty || (t->q_qty % 2 && !t->quote))
	{
		t->quote = ch;
		t->q_qty++;
	}
	else if (!(t->q_qty % 2) && !t->quote)
	{
		t->quote = ch;
		t->q_qty++;
	}
	else if (ch == t->quote)
	{
		t->quote = 0;
		t->q_qty++;
	}
}
