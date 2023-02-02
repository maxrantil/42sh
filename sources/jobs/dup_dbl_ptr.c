/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_dbl_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:26:06 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/01 14:26:36 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It duplicates a double pointer
 * 
 * @param cmd The array of strings to be duplicated.
 * 
 * @return A pointer to a pointer to a char.
 */
char    **dup_dbl_ptr(char **cmd)
{
	int     len;
	char	**dup_arr;

	len = ft_arrlen(cmd);
	dup_arr = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	dup_arr[len] = NULL;
	while (--len >= 0)
		dup_arr[len] = ft_strdup(cmd[len]);
    return (dup_arr);
}
