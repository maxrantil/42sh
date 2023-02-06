/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:09:29 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/26 09:56:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It takes a session and a string, and removes the environment variable that
 * starts with the string.
 *
 * @param sh the session struct
 * @param env_to_clean The environment variable to remove.
 */
void	ft_env_remove(t_shell *sh, char *env_to_clean)
{
	int		i;
	char	**ptr;
	char	**new_array;

	i = 0;
	ptr = sh->env;
	new_array = (char **)ft_memalloc(sizeof(char *) * ft_arrlen(sh->env));
	while (*ptr)
	{
		if (!ft_strnequ(*ptr, env_to_clean, ft_strlen(env_to_clean)))
			*(new_array + (i++)) = ft_strdup(*ptr);
		ptr++;
	}
	*(new_array + (i)) = NULL;
	ft_arrclean(sh->env);
	sh->env = new_array;
}
