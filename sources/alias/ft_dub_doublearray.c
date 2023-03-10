/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dub_doublearray.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:09:29 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/23 15:06:49 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	**ft_dup_doublearray(char **original)
{
	int		size;
	char	**new;
	int		i;

	size = ft_strarray_size(original);
	new = ft_create_empty_str_array(size);
	i = -1;
	while (original[++i])
		new[i] = ft_strdup(original[i]);
	new[i] = NULL;
	return (new);
}
