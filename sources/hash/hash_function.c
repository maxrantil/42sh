/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:19:48 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/26 10:41:07 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
 * This function generates a hash value for the input program string by
 * iterating through each character in the string and performing a series of
 *  arithmetic operations on the hash variable.
 * The resulting hash value is then returned modulo the constant HASH_SIZE.
 */
size_t	hash_function(char *program)
{
	size_t	hash;
	size_t	c;
	int		i;
	int		len;

	hash = 0;
	len = strlen(program);
	i = 0;
	while (i < len)
	{
		c = (size_t)program[i];
		hash = c + (hash << 6) + (hash << 16) - hash;
		i++;
	}
	return (hash % HASH_SIZE);
}
