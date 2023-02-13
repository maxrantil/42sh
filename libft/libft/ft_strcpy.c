/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:07:55 by mbarutel          #+#    #+#             */
/*   Updated: 2021/11/16 14:07:55 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Copy the string pointed to by src, including the terminating null byte 
 * ('\0'), to the buffer pointed to by dst
 * 
 * @param dst This is the destination string.
 * @param src The string to be copied.
 * 
 * @return The address of the destination string.
 */
char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
