/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_tail.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:41:32 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/17 17:39:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It takes a string and a tail and joins them together & frees the tail.
 * 
 * @param head the string to be joined to the beginning of str
 * @param str the string to be freed
 * 
 * @return A pointer to a string.
 */
char	*strjoin_tail(char *head, char *str)
{
	char	*tmp;

	tmp = str;
	str = ft_strjoin(head, str);
	ft_strdel(&tmp);
	return (str);
}
