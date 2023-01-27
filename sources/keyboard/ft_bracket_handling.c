/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bracket_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:46:19 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/27 11:10:28 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void    ft_bracket_handling(t_term *t, int pos)
{
    if (t->bracket == 0 && t->inp[pos] == L_BRAC)
        t->bracket = L_BRAC;
    else if (t->bracket == L_BRAC && t->inp[pos] == R_BRAC)
        t->bracket = 0;
}
