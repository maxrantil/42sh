/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:40:17 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/14 10:42:21 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Write a string to a file descriptor, but only write the first len characters.
 * 
 * @param str The string to be printed.
 * @param fd The file descriptor to write to.
 * @param len The length of the string to be printed.
 */
void	ft_putstr_fd_len(char *str, int fd, int len)
{
	int ignore	__attribute__((unused));

	ignore = write(fd, str, len);
}
