/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delim_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:40:30 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/23 19:35:18 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"
#include "ft_42sh.h"

void	ft_delim_update(t_term *t)
{
	int		len;
	char	*ptr;

	ptr = NULL;
	len = ft_strlen(t->delim);
	if (t->delim && t->delim[len - 1] == '\\')
	{
		// ft_printf("this happens\n");
		ptr = ft_strdup(ft_strstr(t->inp, t->delim));
		ft_strdel(&t->delim);
		t->delim = ptr;
		ft_run_capability("sc");
		ft_setcursor(0, t->ws_row - 2);
		ft_printf("[%s]", t->delim);
		ft_run_capability("rc");
	}
	// else
	// 	ft_quote_blash_removal(t->delim);
}
