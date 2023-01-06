/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_whitespaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:44:05 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/25 14:44:06 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_skip_whitespaces(char *ptr)
{
	if (!ptr)
		return (NULL);
	while (*ptr && ft_isspace((const char *)ptr))
		ptr++;
	return (ptr);
}
