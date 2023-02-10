/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_array_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:02:03 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/09 11:02:41 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

//	duplicate alias-array and remove [pos]
void	dup_arr_rm_pos(char **alias, char ***dup_alias, int pos, int size)
{
	*dup_alias = ft_dup_doublearray(alias);
	remove_alias_single(dup_alias, pos, size);
}

void	free_and_refill_dup_alias(char ***dup_alias, char **original)
{
	ft_free_doublearray(dup_alias);
	*dup_alias = ft_dup_doublearray(original);
}
