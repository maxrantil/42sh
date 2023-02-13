/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:00:29 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/14 10:06:09 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*word_array(const char *str, char c)
{
	int		i;
	char	*ret;

	if (str)
	{
		i = 0;
		while (str[i] != c && str[i] != '\0')
			i++;
		ret = (char *)ft_memalloc(sizeof(char) * (i + 1));
		if (ret)
		{
			i = 0;
			while (str[i] != c && str[i] != '\0')
			{
				ret[i] = str[i];
				i++;
			}
			ret[i] = '\0';
			return (ret);
		}
	}
	return (NULL);
}

static int	word_len(const char *str, int c)
{
	int	index;
	int	words;

	index = 0;
	words = 0;
	if (str)
	{
		while (str[index] != '\0')
		{
			if (str[index] != c && (str[index + 1] == c
					||str[index + 1] == '\0'))
				words++;
			index++;
		}
	}
	return (words);
}

static char	**ft_splitter(char **ret, char const *s, char c, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		while (*s == c)
			s++;
		if (*s != c)
		{
			ret[i] = word_array(s, c);
			if (!ret[i])
			{
				ft_memdel((void **)&ret);
				return (NULL);
			}
		}
		while (*s != c && *s != '\0')
			s++;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

/**
 * It splits a string into words, separated by a character.
 * 
 * @param s the string to be split
 * @param c the character to split on
 * 
 * @return A pointer to a pointer to a char.
 */
char	**ft_strsplit(char const *s, char c)
{
	int		len;
	char	**ret;

	len = word_len(s, c);
	ret = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	if (ret && s)
	{
		ret = ft_splitter(ret, s, c, len);
		return (ret);
	}
	return (NULL);
}
