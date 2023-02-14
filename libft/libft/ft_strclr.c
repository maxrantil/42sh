/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:07:28 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/05 12:34:50 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_strclr() sets every character of the string to the value '\0'
 * 
 * @param s This is the string that needs to be cleared.
 */
void	ft_strclr(char *s)
{
	if (s)
	{
		ft_bzero(s, ft_strlen(s));
	}
}
