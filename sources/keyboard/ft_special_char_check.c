/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_char_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:35:05 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/09 12:48:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It checks if the character `ch` is present in the buffer `buff` at the 
 * position `pos` and if it is, it checks if it is present an odd number
 * of times. This is used for checking backslashes and dollar signs.
 * 
 * @param buff The buffer that contains the string to be checked.
 * @param pos The position of the character in the buffer.
 * @param ch The character to check for.
 */
size_t	special_char_check(char *buff, ssize_t pos, char ch)
{
	ssize_t	index;
	ssize_t	count;

	if (!pos && buff[pos] == ch)
		return (1);
	else if (!pos)
		return (0);
	count = 0;
	index = pos;
	while ((index - 1) >= 0 && buff[index - 1] == ch)
		--index;
	if (index == -1)
		++index;
	while (buff[index] && buff[index] == ch)
		index += ++count;
	if (count && count % 2)
		return (1);
	return (0);
}
