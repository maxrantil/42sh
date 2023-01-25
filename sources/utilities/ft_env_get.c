/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:51:34 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/25 16:16:36 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It takes a session and a key, and returns a pointer to the environment
 * variable with that key.
 *
 * @param sesh The session struct.
 * @param key the key to search for
 *
 * @return A pointer to the environment variable.
 */
char	**ft_env_get(t_session *sesh, char *key)
{
	char	**env;
	char	*key_full;

	env = sesh->env;
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
