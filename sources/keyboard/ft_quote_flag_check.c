/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_flag_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:36:03 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/14 17:37:52 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_quote_flag_check(t_term *t, ssize_t index)
{
	ssize_t	i;

	i = index;
	while (t->inp[i] && t->inp[i] == '\\')
		i++;
	if (t->inp[i] == S_QUO || t->inp[i] == D_QUO)
		ft_quote_flag_reset(t);
}
