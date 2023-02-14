/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_head.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:40:55 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/17 17:38:29 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It takes a string and a tail and joins them together & frees the head.
 * 
 * @param str The string to be appended to.
 * @param tail the string to be appended to the end of str
 * 
 * @return A pointer to a string.
 */
char	*strjoin_head(char *str, char *tail)
{
	char	*tmp;

	tmp = str;
	str = ft_strjoin(str, tail);
	ft_strdel(&tmp);
	return (str);
}
