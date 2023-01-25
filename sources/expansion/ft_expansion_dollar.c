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

#include "ft_21sh.h"

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
		if (!i || (ft_isspecial(str[i]) && str[i] != '_'))
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
		if (ft_isspecial(str[i]) && str[i] != '_')
			i++;
		while (str[i] && (!ft_isspecial(str[i]) || str[i] == '_'))
			i++;
		ret[j++] = ft_strsub(str, 0, i);
		str += i;
	}
	ret[j] = NULL;
	return (ret);
}

/**
 * It takes a string, finds the first instance of a dollar sign, and replaces
 * it with the value of the environment variable that follows the dollar sign
 *
 * @param sesh the session struct
 * @param buff the buffer to write to
 * @param arg the string to be parsed
 */
static char	*ft_find_env(t_session *sesh, char *arg)
{
	char	*ret;
	char	*key;
	char	**env;
	int		key_len;

	ret = NULL;
	key_len = 0;
	while (arg[key_len] && !ft_isspace(arg[key_len]))
		key_len++;
	key = ft_strsub(arg, 1, key_len - 1);
	env = ft_env_get(sesh, key);
	if (env)
		ret = ft_strdup(ft_strchr(*env, '=') + 1);
	else
		ret = ft_strnew(1);
	if (arg[key_len])
		ret = strjoin_head(ret, arg + key_len);
	ft_strdel(&key);
	return (ret);
}

/**
 * It takes a string, splits it on the '$' character, and then catinates the
 * expansion of the split strings.
 *
 * @param sesh the session struct
 * @param split_dollar This is the string that is being split by the dollar sign.
 * @param buff This is the buffer that will be returned.
 */
static void	catinate_expansion(t_session *sesh, char **splits, char **buff)
{
	char	*tofree;

	tofree = NULL;
	if (**splits == '$' && ft_strlen(*splits) > 1)
	{
		if (!*buff)
			*buff = ft_find_env(sesh, *splits);
		else
		{
			tofree = ft_find_env(sesh, *splits);
			*buff = strjoin_head(*buff, tofree);
			ft_strdel(&tofree);
		}
	}
	else
	{
		if (!*buff)
			*buff = ft_strdup(*splits);
		else
			*buff = strjoin_head(*buff, *splits);
	}
	ft_strdel(splits);
}

/**
 * It takes a string, splits it on special characters, and then replaces any
 * dollar signs with the value of the environment variable that follows it.
 *
 * @param sesh the session struct
 * @param str the string to be expanded
 *
 * @return A string
 */
char	*ft_expansion_dollar(t_session *sesh, char *str)
{
	int		i;
	char	*buff;
	char	**split_dollar;

	i = -1;
	buff = NULL;
	if (!ft_strcmp(str, "$$"))
		return (ft_itoa(getpid()));
	if (!ft_strcmp(str, "$?"))
		return (ft_itoa(sesh->exit_stat));
	split_dollar = ft_special_ch_split(str);
	while (split_dollar[++i])
		catinate_expansion(sesh, &split_dollar[i], &buff);
	ft_memdel((void **)&split_dollar);
	return (buff);
}
