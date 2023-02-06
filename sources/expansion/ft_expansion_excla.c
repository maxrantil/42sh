/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_excla.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:57:35 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/26 10:53:14 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_term	*g_t;

char	*ft_expansion_excla(char *str, int i)
{
	char *begin;
	char *end;
	char *ret;

	i = 0;
	while (str[i] && str[i] != '!')
		i++;
	begin = ft_strsub(str, 0, i);
	end = ft_strdup(str + i + 2);
	ret = ft_strjoin_three(begin, g_t->history_arr[g_t->history_size - 2], str + i + 2);
	ft_strdel(&begin);
	ft_strdel(&end);
	return (ret);
}
