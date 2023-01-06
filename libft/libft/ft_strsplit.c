/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:35:23 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:27:47 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_freemal(char **ret, int index)
{
	while (index--)
	{
		if (ret[index])
			free(ret[index]);
	}		
	free(ret);
	return (NULL);
}

static int	word_count(char const *s, char c)
{
	int	state;
	int	wc;

	wc = 0;
	state = OUT;
	while (*s)
	{
		if (*s == c)
			state = OUT;
		else if (state == OUT)
		{
			state = IN;
			++wc;
		}
		++s;
	}
	return (wc);
}

static char	**make_ret(char const *s, char c, char **ret)
{
	t_strsplit	a;

	a.i = 0;
	a.index = 0;
	while (s[a.i])
	{
		while (s[a.i] == c)
			a.i++;
		a.e = a.i;
		if (s[a.i] == '\0')
			break ;
		while (s[a.e] != c)
		{
			a.e++;
			if (!s[a.e])
				break ;
		}
		ret[a.index] = ft_strsub(s, a.i, a.e - a.i);
		if (!ret[a.index])
			return (ft_freemal(ret, a.index));
		a.index++;
		a.i = a.e;
	}
	ret[a.index] = NULL;
	return (ret);
}

char	**ft_strsplit(char const *s, char c)
{
	char		**ret;

	if (!s)
		return (NULL);
	ret = (char **)ft_memalloc(sizeof(char *) * word_count(s, c) + 1);
	if (!ret)
		return (NULL);
	ret = make_ret(s, c, ret);
	return (ret);
}
