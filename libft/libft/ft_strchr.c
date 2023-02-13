/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:07:20 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/08 22:17:30 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The function ft_strchr() takes a string and a character as arguments and
 * returns a pointer to the first occurrence of the character in the string
 * 
 * @param str The string to be searched.
 * @param c The character to be located.
 * 
 * @return A pointer to the first occurrence of the character c in the string.
 */
char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (0);
}
