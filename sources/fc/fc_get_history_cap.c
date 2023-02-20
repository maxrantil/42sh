/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_get_history_cap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:44:45 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/20 17:44:57 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	get_history_cap(t_shell *sh)
{
	if (sh->term->history_size < 500)
		return (0);
	else
		return (sh->term->history_size - 500);
}
