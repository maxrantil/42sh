/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_temp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:19:22 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/06 12:59:23 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It returns the number of
 * strings in the array that are environment variables.
 * 
 * @param cmd the command line
 * 
 * @return The number of elements in the array that are not NULL and contain 
 * an '='
 */
static int	tmp_env_len(char **cmd)
{
	int	len;

	len = 0;
	while (*(cmd + len) && ft_strchr(*(cmd + len), '=') \
		&& *(*(cmd + len)) != '=')
		len++;
	return (len);
}

/**
 * It takes the temporary environment variables and stores them in a 2D array
 * 
 * @param sesh the session struct
 * @param cmd the command line arguments
 * @param i the index of the command line argument
 * 
 * @return The index of the command after the last environment variable.
 */
int	ft_env_temp(t_session *sesh, char **cmd, int i)
{
	int		j;
	char	*replaced;

	j = 0;
	replaced = NULL;
	sesh->tmp_env_key = (char **)ft_memalloc(sizeof(char *) * \
		(tmp_env_len(cmd + i) + 1));
	while (*(cmd + i) && ft_strchr(*(cmd + i), '=') && *(*(cmd + i)) != '=')
	{
		if (ft_env_replace(sesh, *(cmd + i), &replaced))
			*(sesh->tmp_env_key + j++) = replaced;
		else
		{
			ft_env_append(sesh, cmd + i);
			*(sesh->tmp_env_key + j++) = ft_strsub(*(cmd + i), 0, \
				ft_strchr(*(cmd + i), '=') - *(cmd + i));
		}
		i++;
	}
	*(sesh->tmp_env_key + j) = NULL;
	return (i);
}
