/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bslash_escape_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:06:01 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/16 16:26:25 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

int	ft_bslash_escape_check(t_term *t, ssize_t pos)
{
	ssize_t	start;
	ssize_t	count;

	if (!pos)
		return (0);
	start = pos - 1;
	while (start && t->inp[start] == '\\')
		start--;
	if (start)
		start++;
	count = start;
	while (count < t->bytes && t->inp[count] == '\\')
		count++;
	if ((count - start) % 2)
		return (1);
	return (0);
}
