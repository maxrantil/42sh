/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspecial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 20:05:05 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 13:23:25 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It returns 1 if the character is a special character, and 0 if it isn't
 * 
 * @param c The character to be checked.
 * 
 * @return 1 if the character is a special character, otherwise it returns 0.
 */

int	ft_isspecial(int c)
{
	if (!ft_isalnum(c) && !ft_isspace(c) && !ft_isdigit(c))
		return (1);
	return (0);
}
