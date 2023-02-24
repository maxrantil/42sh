/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delim_bslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:10:21 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/24 10:21:01 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

int	ft_delim_bslash(char *ptr, int pos)
{
	int	count;

	count = 0;
	while (pos-- >= 0 && ptr[pos + 1] == '\\')
		++count;
	if (!count || count % 2 == 0)
		return (0);
	else
		return (1);
}
