/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alt_mv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:05:53 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 16:35:15 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It handles the movement of the cursor when the user presses the alt key
 *
 * @param t the t_term struct
 */
void	ft_alt_mv(t_term *t)
{
	if (t->ch == ALT_LFT || t->ch == ALT_RGHT)
		ft_word_mv(t);
	else if (t->ch == LINE_MV)
		ft_line_mv(t);
}
