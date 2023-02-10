/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:53:47 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/06 16:48:06 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "libft.h"

int	ft_strarray_size(char **arr)
{
	int	i;

	if (!arr || !arr[0])
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
