/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:11:23 by mbarutel          #+#    #+#             */
/*   Updated: 2021/11/16 14:11:23 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * If the character is uppercase, convert it to lowercase
 * 
 * @param c The character to be converted.
 * 
 * @return The lowercase version of the character.
 */
int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c = c + (97 - 65);
	return (c);
}
