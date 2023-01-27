/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_search_history.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:33:56 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/27 15:03:19 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	set_signal_search_history(void)
{
	int	sig;

	sig = -1;
	while (++sig < 32)
		signal(sig, search_history_sigs);
}
