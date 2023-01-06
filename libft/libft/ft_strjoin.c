/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:05:00 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/30 12:43:59 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*sj;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	sj = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (!sj)
		return (NULL);
	while (s1[i])
	{
		sj[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		sj[i] = s2[j];
		i++;
		j++;
	}
	sj[i] = '\0';
	return (sj);
}
