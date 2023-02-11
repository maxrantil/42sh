/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_globstars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:33:53 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 17:03:07 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	remove_globstars(char **needle, int *glob)
{
	int	len;

	*glob = 0;
	len = ft_strlen(*needle);
	while (**needle == '*')
	{
		*glob = 1;
		(*needle)++;
	}
	while ((*needle)[len - 1] == '*')
	{
		*glob = 3;
		(*needle)[len - 1] = '\0';
		len--;
	}
}
