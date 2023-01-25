/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:42:26 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/16 13:13:11 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
 * the `env` variable of the `t_session` structure
 *
 * @param sesh The session struct.
 */
void	ft_env_init(t_session *sesh)
{
	int		i;

	i = -1;
	sesh->env = (char **)ft_memalloc(sizeof(char *) * (ft_arrlen(environ) + 1));
	sesh->intr_vars = (char **)ft_memalloc(sizeof(char *) * 100);
	while (environ[++i])
	{
		if (ft_strstr(environ[i], "SHLVL="))
			sesh->env[i] = ft_shlvl(environ[i]);
		else
			sesh->env[i] = ft_strdup(environ[i]);
	}
	sesh->env[i] = NULL;
	if (ft_env_get(sesh, "OLDPWD"))
		ft_env_remove(sesh, "OLDPWD=");
}
