/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:23:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 13:19:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * This function skips all whitespace characters in a string and returns a
 * pointer to the first non-whitespace character
 * 
 * @param str The string to be searched.
 * 
 * @return A pointer to the first non-whitespace character in the string.
 */
char	*ft_skip_space(char *str)
{
	if (str)
	{
		while (*str)
		{
			if (!ft_isspace(*str))
				return (str);
			str++;
		}	
	}
	return (NULL);
}
