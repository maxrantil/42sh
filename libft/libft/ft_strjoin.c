/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:08:53 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/07 18:12:14 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_joiner(char *ret, char const *s1, char const *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
}

/**
 * It takes two strings and joins them together.
 * 
 * @return A pointer to a string.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*ret;

	if (s1 && s2)
	{
		len = (ft_strlen(s1) + ft_strlen(s2));
		ret = (char *)ft_memalloc(sizeof(char) * (len + 1));
		if (ret)
		{
			ft_joiner(ret, s1, s2);
			return (ret);
		}
	}
	return (NULL);
}
