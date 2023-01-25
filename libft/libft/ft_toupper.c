/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:11:31 by mbarutel          #+#    #+#             */
/*   Updated: 2021/11/17 15:17:03 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * If the character is lowercase, convert it to uppercase
 * 
 * @param c The character to be converted.
 * 
 * @return The uppercase version of the character.
 */
int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c = c - (97 - 65);
	return (c);
}
