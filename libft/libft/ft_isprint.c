/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:03:55 by mbarutel          #+#    #+#             */
/*   Updated: 2021/11/19 14:03:51 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * If the character is between 32 and 126, return 1, otherwise return 0
 * 
 * @param c The character to be checked.
 * 
 * @return 1 or 0
 */
int	ft_isprint(int c)
{
	if ((c >= 32) && (c <= 126))
		return (1);
	return (0);
}
