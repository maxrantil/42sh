/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:36:51 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/26 10:37:02 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_freeda(void ***a, size_t row)
{
	unsigned int	i;

	i = -1;
	if (!a || !*a)
		return (1);
	while ((*a)[++i] && i < row)
		ft_strdel((char **)&(*a)[i]);
	ft_memdel((void **)a);
	return (1);
}
