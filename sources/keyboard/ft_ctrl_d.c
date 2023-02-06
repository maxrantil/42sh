/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:22:14 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/26 10:24:56 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

int	ctrl_d(t_term *t)
{
	if (!t->bytes)
	{
		if (t->clipboard.buff)
			ft_strdel(&t->clipboard.buff);
		return (-1);
	}
	if (t->index < t->bytes)
		ft_delete(t);
	if (t->heredoc && !*t->nl_addr[t->c_row])
	{
		ft_putstr("42sh: warning: here-document at line ");
		ft_putnbr((int)t->c_row);
		ft_putstr(" delimited by end-of-file (wanted `EOF')");
		ft_delim_fetch(t);
		ft_strcat(t->inp, t->delim);
		ft_end_cycle(t);
		return (1);
	}
	return (0);
}
