/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:24:39 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/12 12:30:53 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It moves the cursor up to the end of the line
 *
 * @param t the term structure
 * @param len the length of the line
 * @param prompt_len The length of the prompt.
 */
static void	ft_move_up_end_line(t_term *t, ssize_t len, ssize_t prompt_len)
{
	t->c_col = len + prompt_len;
	t->index = (t->nl_addr[t->c_row] - t->nl_addr[0]) - 1;
}

/*
 * If the cursor is on the first line, move it to the beginning of the line.
 * Otherwise, move it to the beginning of the previous line.
 *
 * @param t the term structure
 * @param prompt_len the length of the prompt
 */
static void	ft_move_up(t_term *t, ssize_t prompt_len)
{
	ssize_t	len;

	len = prompt_len;
	if (t->c_col < len)
	{
		t->c_col = len;
		if (t->c_row == 1)
			t->index = 0;
		else
			t->index = t->nl_addr[t->c_row - 1] - t->nl_addr[0];
	}
	else
		t->index = (&t->nl_addr[t->c_row - 1]
			[t->c_col - prompt_len] - t->nl_addr[0]);
}

/*
 * It moves the cursor up one line
 *
 * @param t the term structure
 */
void	ft_line_up(t_term *t)
{
	ssize_t	len;
	ssize_t	prompt_len;

	len = t->nl_addr[t->c_row] - t->nl_addr[t->c_row - 1] - 1;
	prompt_len = ft_get_prompt_len(t, t->c_row - 1);
	if (t->c_row == 1)
		prompt_len += t->term_val[0];
	if (t->c_col < (len + prompt_len))
		ft_move_up(t, prompt_len);
	else
		ft_move_up_end_line(t, len, prompt_len);
	ft_setcursor(t->c_col, t->term_val[1] + --t->c_row);
}
