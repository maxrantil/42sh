/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mv_prompt_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:23:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 17:13:38 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It returns the length of the prompt on the line that the cursor will be
 * on after the movement
 *
 * @param t the term structure
 * @param num the number of lines to move
 *
 * @return The length of the prompt.
 */
ssize_t	ft_mv_prompt_len(t_term *t, int num)
{
	ssize_t	prompt_len;

	prompt_len = 0;
	if (t->c_row == 1 && (num < 0))
		prompt_len = t->prompt_len;
	else if (ft_is_prompt_line(t, t->c_row + num))
		prompt_len = t->m_prompt_len;
	return (prompt_len);
}
