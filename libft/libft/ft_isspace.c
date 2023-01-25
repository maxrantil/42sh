/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 10:57:33 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/23 13:21:46 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The function ft_isspace() returns 1 if the character c is a whitespace
 * character, and 0 otherwise
 * 
 * @param c The character to be checked.
 * 
 * @return the number of words in the string.
 */
int	ft_isspace(int c)
{
	if (c >= 9 && c <= 13)
		return (1);
	if (c == 32)
		return (1);
	return (0);
}
