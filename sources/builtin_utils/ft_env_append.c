/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:12:44 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/01 18:17:23 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It takes a session and an array of strings, and appends the first string
 * in the array to the session's environment.
 * 
 * @param sesh the session struct
 * @param arg The argument to be appended to the environment.
 * 
 * @return The return value is the index of the first occurrence of the character
 * c in the string s.
 */
int	ft_env_append(t_session *sesh, char **arg)
{
	int		i;
	char	**new_array;

	i = -1;
	new_array = (char **)ft_memalloc(sizeof(char *) * \
	(ft_arrlen(sesh->env) + 2));
	while (sesh->env[++i])
		new_array[i] = ft_strdup(sesh->env[i]);
	new_array[i++] = ft_strdup(*arg);
	new_array[i] = NULL;
	ft_arrclean(sesh->env);
	sesh->env = new_array;
	return (0);
}
