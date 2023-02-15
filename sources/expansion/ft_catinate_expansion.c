/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_catinate_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:22:40 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/14 15:54:47 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It takes a string, finds the first instance of a dollar sign, and replaces
 * it with the value of the environment variable that follows the dollar sign
 *
 * @param sh the session struct
 * @param buff the buffer to write to
 * @param arg the string to be parsed
 */
static char	*ft_find_env(t_shell *sh, char *arg)
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
	env = ft_env_get(sh, key, sh->env);
	if (env)
		ret = ft_strdup(ft_strchr(*env, '=') + 1);
	else if (!ret)
	{
		env = ft_env_get(sh, key, sh->intr_vars);
		if (env && *env)
			ret = ft_strdup(ft_strchr(*env, '=') + 1);
		else
			ret = ft_strnew(1);
	}
	else
		ret = ft_strnew(1);
	if (arg[key_len])
		ret = strjoin_head(ret, arg + key_len);
	ft_strdel(&key);
	return (ret);
}

static void	dollar_questionmark(t_shell *sh, char **splits, char ***str)
{
	**str = ft_itoa(sh->exit_stat);
	if (*(*splits + 2))
		**str = strjoin_head(**str, *splits + 2);
}

static void	if_buf(t_shell *sh, char **splits, char **buff, char **tofree)
{
	if (ft_strncmp(*splits, "$?", 2) == 0)
		dollar_questionmark(sh, splits, &tofree);
	else
		*tofree = ft_find_env(sh, *splits);
	*buff = strjoin_head(*buff, *tofree);
	ft_strdel(tofree);
}

/**
 * It takes a string, splits it on the '$' character, and then catinates the
 * expansion of the split strings.
 *
 * @param sh the session struct
 * @param split_dollar This is the string that is being split by the dollar sign.
 * @param buff This is the buffer that will be returned.
 */
void	ft_catinate_expansion(t_shell *sh, char **splits, \
								char **buff, char qoute)
{
	char	*tofree;

	tofree = NULL;
	if (qoute != '\'' && **splits == '$' && ft_strlen(*splits) > 1)
	{
		if (!*buff)
		{
			if (ft_strncmp(*splits, "$?", 2) == 0)
				dollar_questionmark(sh, splits, &buff);
			else
				*buff = ft_find_env(sh, *splits);
		}
		else
			if_buf(sh, splits, buff, &tofree);
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
