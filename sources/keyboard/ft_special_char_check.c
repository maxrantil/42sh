/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_char_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:35:05 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/27 16:35:10 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

size_t	special_char_check(char *buff, ssize_t pos, char ch)
{
	ssize_t	start;
	ssize_t	count;

	if (!pos)
		return (0);
	start = pos - 1;
	while (start && buff[start] == ch)
		start--;
	if (start)
		start++;
	count = start;
	while (buff[count] && buff[count] == ch)
		count++;
	if ((count - start) % 2)
		return (1);
	return (0);
}
