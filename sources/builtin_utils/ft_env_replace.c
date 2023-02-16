/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:12:18 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/15 20:10:24 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It takes a session, an environment variable name, and a pointer to a pointer
 * to a string. It then searches the session's environment for the variable name,
 * and if it finds it, it replaces the value of the variable with the value of
 * the string that the pointer to a pointer to a string points to.
 *
 * @param sh the session struct
 * @param envn The environment variable to replace.
 * @param tmp_env if this is not NULL, then the old environment variable will
 * be stored
 */
int	ft_env_replace(t_shell *sh, char *envn, char **tmp_env)
{
	int		ret;
	char	*key;
	char	**envp;

	ret = 0;
	key = ft_strsub(envn, 0, ft_strchr(envn, '=') - envn);
	envp = ft_env_get(sh, key, sh->env);
	if (envp)
	{
		if (tmp_env)
			*tmp_env = *envp;
		else
			ft_strdel(envp);
		*envp = ft_strdup(envn);
		add_var_env_quotes(envp);
		ret = 1;
	}
	ft_strdel(&key);
	return (ret);
}
