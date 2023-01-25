/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:09:29 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/06 12:57:30 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It takes a session and a string, and removes the environment variable that
 * starts with the string.
 * 
 * @param sesh the session struct
 * @param env_to_clean The environment variable to remove.
 */
void	ft_env_remove(t_session *sesh, char *env_to_clean)
{
	int		i;
	char	**ptr;
	char	**new_array;

	i = 0;
	ptr = sesh->env;
	new_array = (char **)ft_memalloc(sizeof(char *) * ft_arrlen(sesh->env));
	while (*ptr)
	{
		if (!ft_strnequ(*ptr, env_to_clean, ft_strlen(env_to_clean)))
			*(new_array + (i++)) = ft_strdup(*ptr);
		ptr++;
	}
	*(new_array + (i)) = NULL;
	ft_arrclean(sesh->env);
	sesh->env = new_array;
}
