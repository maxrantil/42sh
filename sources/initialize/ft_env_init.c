/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:42:26 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/02 15:04:53 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern char	**environ;

/**
 * It increments the level number in the environment variable.
 *
 * @param env the environment variable that we want to change
 *
 * @return The return value is the number of bytes that were written to the
 * file.
 */
static char	*increment_lvl(char *env)
{
	int		lvl;

	lvl = ft_atoi(ft_strchr(env, '=') + 1);
	if (lvl < 1000)
		lvl++;
	else
		lvl = 0;
	return (ft_itoa(lvl));
}

/**
 * It takes the environment variable SHLVL, increments it by one.
 *
 * @param my_env the environment variable that will be added to the environment
 * @param env the environment variable that we're looking for
 *
 * @return a string that is the SHLVL environment variable.
 */
static char	*ft_shlvl(char *shlvl)
{
	char	*lvl;
	char	*env;

	lvl = increment_lvl(shlvl);
	env = ft_strjoin("SHLVL=", lvl);
	ft_strdel(&lvl);
	return (env);
}

/**
 * It copies the environment variables from the global variable `environ` into
 * the `env` variable of the `t_shell` structure
 *
 * @param sh The session struct.
 */
void	ft_env_init(t_shell *sh)
{
	int		i;

	i = -1;
	sh->env = (char **)ft_memalloc(sizeof(char *) * (ft_arrlen(environ) + 1));
	sh->intr_vars = (char **)ft_memalloc(sizeof(char *) * 100);
	while (environ[++i])
	{
		if (ft_strstr(environ[i], "SHLVL="))
			sh->env[i] = ft_shlvl(environ[i]);
		else
			sh->env[i] = ft_strdup(environ[i]);
	}
	sh->env[i] = NULL;
	if (ft_env_get(sh, "OLDPWD", sh->env))
		ft_env_remove(sh, "OLDPWD=");
}
