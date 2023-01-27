/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:36:54 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 19:19:03 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit_loop(char *str)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
	{
		if ((str[i] == '-' || str[i] == '+') && i == 0)
			continue ;
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}
