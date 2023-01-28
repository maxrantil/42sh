/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:40:21 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/26 10:40:33 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	size_t	total;
	char	*new;

	if (!s1 || !s2 || !s3)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	new = ft_strnew(total);
	if (new != NULL)
	{
		new = ft_strcpy(new, (const char *)s1);
		new = ft_strcat(new, (const char *)s2);
		new = ft_strcat(new, (const char *)s3);
	}
	return (new);
}
