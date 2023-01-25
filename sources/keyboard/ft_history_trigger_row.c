/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_trigger_row.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:04:22 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/12 16:07:37 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

ssize_t	ft_history_trigger_row(t_term *t)
{
	ssize_t	row;

	if (t->history_row == -1)
	{
		row = t->c_row;
		while (row && !ft_is_prompt_line(t, row))
			row--;
	}
	else
		row = t->history_row;
	return (row);
}
