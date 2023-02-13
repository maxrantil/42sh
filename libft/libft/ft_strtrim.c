/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.o                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:11:13 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/07 18:12:59 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_start(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

static size_t	ft_end(char const *str)
{
	size_t	end;

	end = ft_strlen(str) - 1;
	while (&str[end] > str && ft_isspace(str[end]))
		end--;
	return (end);
}

/**
 * It takes a string and returns a copy of the string with the leading and
 * trailing whitespace removed.
 * 
 * @return A pointer to a new string.
 */
char	*ft_strtrim(char const *str)
{
	size_t	start;
	size_t	end;

	if (str)
	{
		start = ft_start(str);
		end = ft_end(str) + 1;
		if (start < end)
			return (ft_strsub(str, start, end - start));
	}
	return (NULL);
}
