/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:57:25 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/11 11:03:7 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It counts the number of special characters in a string
 *
 * @param str The string to be split.
 *
 * @return The number of special characters in the string.
 */
static int	ft_special_ch_split_len(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (!i || (ft_isspecial(str[i]) && str[i] != '_' && str[i] != '?'))
			len++;
	}
	return (len);
}

/**
 * It splits a string intovan array of strings, where each string is a word, and
 * a word is defined as a sequence of characters that are not special characters
 *
 * @param str the string to be split
 *
 * @return A pointer to a pointer to a char.
 */
static char	**ft_special_ch_split(char *str)
{
	int		i;
	int		j;
	char	**ret;

	j = 0;
	ret = (char **)ft_memalloc(sizeof(char *) * \
	(ft_special_ch_split_len(str) + 1));
	while (*str)
	{
		i = 0;
		if (ft_isspecial(str[i]) && str[i] != '_' && str[i] != '?')
			i++;
		while (str[i] \
			&& (!ft_isspecial(str[i]) || str[i] == '_' || str[i] == '?'))
			i++;
		ret[j++] = ft_strsub(str, 0, i);
		str += i;
	}
	ret[j] = NULL;
	return (ret);
}

/**
 * Monitors the inclusion of qoutes and any back slashes before the quote
 */
static void	qoute_check(char **split, int index, char *qoute, char *ch)
{
	int	bslash;

	bslash = 0;
	while ((index - 1) > 0 && split[index - 1]
		&& !ft_strcmp(split[index - 1], "\\"))
	{
		bslash++;
		index--;
	}
	if (bslash % 2 == 0)
	{
		if (*qoute == 0)
			*qoute = *ch;
		else if (*qoute == *ch)
			*qoute = 0;
	}
}

/**
 * It takes a string, splits it on special characters, and then replaces any
 * dollar signs with the value of the environment variable that follows it.
 *
 * @param sh the session struct
 * @param str the string to be expanded
 *
 * @return A string
 */
char	*ft_expansion_dollar(t_shell *sh, char *str)
{
	int		i;
	char	qoute;
	char	*buff;
	char	**split_dollar;

	i = -1;
	qoute = 0;
	buff = NULL;
	if (!ft_strcmp(str, "$$"))
		return (ft_itoa(getpid()));
	split_dollar = ft_special_ch_split(str);
	while (split_dollar[++i])
	{
		if (!ft_strcmp(split_dollar[i], "\'")
			|| !ft_strcmp(split_dollar[i], "\""))
			qoute_check(split_dollar, i, &qoute, split_dollar[i]);
		ft_catinate_expansion(sh, &split_dollar[i], &buff, qoute);
	}
	ft_memdel((void **)&split_dollar);
	return (buff);
}
