/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_braces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:31:22 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/07 11:31:35 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*remove_braces(char *str)
{
	int		i;

	i = 1;
	if (!str[1] || str[1] != '{')
		return (str);
	str[1] = str[2];
	str[ft_strlen(str) - 1] = '\0';
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	return (str);
}
