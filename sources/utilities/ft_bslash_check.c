/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bslash_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:03:10 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/27 11:00:09by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

size_t	ft_bslash_check(char *buff, ssize_t pos)
{
	size_t	len;
	ssize_t	count;

	len = 0;
	count = pos - 1;
	while (buff[count] == '\\')
	{
		len++;
		if (!count)
			break ;
		count--;
	}
	if (len && (len % 2))
		return (1);
	return (0);
}

// size_t	special_char_check(char *buff, ssize_t pos, char ch)
// {
// 	size_t	len;
// 	ssize_t	count;

// 	len = 0;
// 	count = pos - 1;
// 	while (buff[count] == ch)
// 	{
// 		len++;
// 		if (!count)
// 			break ;
// 		count--;
// 	}
// 	if (len && (len % 2))
// 		return (1);
// 	return (0);
// }
