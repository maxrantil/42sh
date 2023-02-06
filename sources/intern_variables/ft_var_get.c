/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:50:14 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/26 09:56:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	**ft_var_get(t_shell *sh, char *key, int *count)
{
	char	**vars;
	char	*key_full;

	vars = sh->intr_vars;
	key_full = ft_strjoin(key, "=");
	while (*vars)
	{
		if (ft_strnequ(*vars, key_full, ft_strlen(key_full)))
		{
			ft_strdel(&key_full);
			return (vars);
		}
		*count += 1;
		vars++;
	}
	ft_strdel(&key_full);
	return (NULL);
}
