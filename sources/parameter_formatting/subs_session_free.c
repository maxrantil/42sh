/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subs_session_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:23:22 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/11 11:21:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	subs_session_free(t_sub *sub)
{
	ft_strdel(&sub->needle);
	ft_strdel(&sub->strip);
	ft_strdel(&sub->haystack);
	ft_strdel(&sub->temp_hays);
}
