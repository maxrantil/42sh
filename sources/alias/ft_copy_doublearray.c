/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_doublearray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:12:18 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/06 16:48:25 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "libft.h"

void	ft_copy_doublearray(char **src, char **dst)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = ft_strdup(src[i]);
}
