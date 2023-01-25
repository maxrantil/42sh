/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:19:54 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/13 13:13:31 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	is_logicalop(int token)
{
	return (token == LOGICAL_AND || token == LOGICAL_OR);
}

int	is_semicolon_or_ampersand(int token)
{
	return (token == SEMICOLON || token == AMPERSAND);
}
