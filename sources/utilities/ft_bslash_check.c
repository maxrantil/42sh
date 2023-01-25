/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blash_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:03:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/29 12:03:37 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
