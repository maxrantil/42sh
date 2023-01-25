/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 10:24:31 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/17 17:45:04 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charcmp(const char c, const char *delim)
{
	while (delim[0] != '\0')
	{
		if (c == delim[0])
			return (1);
		delim++;
	}
	return (0);
}

/**
 * It takes a string and a delimiter, and returns a pointer to the first 
 * character of the string that is not a delimiter
 * 
 * @param stringp This is a pointer to a pointer to a character.
 * @param delim The delimiter string.
 * 
 * @return A pointer to the first token found in the string.
 */
char	*ft_strsep(char **stringp, const char *delim)
{
	int		i;
	char	*ptr;

	if (stringp)
	{
		i = 0;
		ptr = *stringp;
		while (stringp[0][i] != '\0' && ft_charcmp(stringp[0][i], delim) == 0)
			i++;
		if (stringp[0][i] == '\0')
			*stringp = NULL;
		else
		{
			stringp[0][i] = '\0';
			*stringp = &stringp[0][i + 1];
		}
		return (ptr);
	}
	return (NULL);
}
