/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_tilde.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:57:35 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/13 20:49:14 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It returns the environment variable name that corresponds to the tilde key
 *
 * @param str The string to be expanded.
 *
 * @return The key for the environment variable.
 */
static char	*tilde_key(char *str, int *stilde)
{
	if (!ft_strcmp(str, "~+"))
		return ("PWD");
	else if (!ft_strcmp(str, "~-"))
		return ("OLDPWD");
	else if (*str == '~')
	{
		*stilde = 1;
		return ("HOME");
	}
	return (NULL);
}

static char	*stilde_join(char *env, char *str)
{
	if (*(str + 1) == '/')
		return (ft_strjoin(env, str + 1));
	else if (ft_strlen(str) == 1)
		return (ft_strdup(env));
	return (ft_strdup(str));
}

static int	init_user(char *str, char **user)
{
	*user = user_expansions(str);
	if (*user)
		return (1);
	return (0);
}

/**
 * It takes a string and returns a string with the tilde expanded.
 *
 * @param sh the session struct
 * @param str the string to be expanded
 *
 * @return The value of the key in the environment.
 */
char	*ft_expansion_tilde(t_shell *sh, char *str)
{
	char	*key;
	char	**env;
	int		stilde;
	char	*user;

	env = NULL;
	stilde = 0;
	key = tilde_key(str, &stilde);
	if (init_user(str, &user))
		return (user);
	if (key)
	{
		env = ft_env_get(sh, key, sh->env);
		if (env)
		{
			if (stilde)
				return (stilde_join(ft_strchr(*env, '=') + 1, str));
			else
				return (ft_strdup(ft_strchr(*env, '=') + 1));
		}
	}
	return (ft_strdup(str));
}
