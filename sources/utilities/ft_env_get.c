/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:51:34 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/02 15:06:44 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It takes a session and a key, and returns a pointer to the environment
 * variable with that key.
 *
 * @param sh The session struct.
 * @param key the key to search for
 *
 * @return A pointer to the environment variable.
 */
char	**ft_env_get(t_shell *sh, char *key, char **from_array)
{
	char	**env;
	char	*key_full;

	(void)sh;
	env = from_array;
	key_full = ft_strjoin(key, "=");
	while (*env)
	{
		if (ft_strnequ(*env, key_full, ft_strlen(key_full)))
		{
			ft_strdel(&key_full);
			return (env);
		}
		env++;
	}
	ft_strdel(&key_full);
	return (NULL);
}
