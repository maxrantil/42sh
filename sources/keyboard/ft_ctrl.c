/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:36:28 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/25 13:19:34 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It handles the control keys
 *
 * @param t the term structure
 */
void	ft_ctrl(t_term *t)
{
	if (t->ch == CTRL_W)
		ft_cut(t);
	else if (t->ch == CTRL_U)
		ft_copy(t);
	else if (t->ch == CTRL_P)
		ft_paste(t);
	else if (t->ch == CTRL_L)
	{
		t->term_val[1] = 0;
		ft_run_capability("vi");
		ft_run_capability("cl");
		ft_print_input(t, 0, 0);
		set_new_cur_pos(t);
		ft_run_capability("ve");
	}
	else if (t->ch == CTRL_R && t->c_row == t->total_row \
	&& ft_is_prompt_line(t, t->total_row))
		ft_search_history(t);
}
