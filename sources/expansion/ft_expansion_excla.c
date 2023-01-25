/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_excla.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:57:35 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/12 16:49:48 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern t_term	*g_t;

static char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	size_t	total;
	char	*new;

	if (!s1 || !s2 || !s3)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	new = ft_strnew(total);
	if (new != NULL)
	{
		new = ft_strcpy(new, (const char *)s1);
		new = ft_strcat(new, (const char *)s2);
		new = ft_strcat(new, (const char *)s3);
	}
	return (new);
}


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
