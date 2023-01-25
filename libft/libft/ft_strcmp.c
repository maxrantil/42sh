/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:07:35 by mbarutel          #+#    #+#             */
/*   Updated: 2021/11/16 14:07:35 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The function compares the two strings s1 and s2. It returns an integer less
 * than, equal to, or greater than zero if s1 is found, respectively, to be
 * less than, to match, or be greater than s2
 * 
 * @param s1 The first string to be compared.
 * @param s2 the string to be compared to s1
 * 
 * @return The difference between the first two characters that do not match.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] ^ '\0') && (s2[i] != '\0') && ((s1[i] ^ s2[i]) == 0))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
