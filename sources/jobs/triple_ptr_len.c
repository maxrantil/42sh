/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triple_ptr_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:21:41 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/08 10:42:42 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It returns the length of a triple pointer
 * 
 * @param arr The array of strings to be freed.
 * 
 * @return The length of the array of strings.
 */
size_t	triple_ptr_len(char ***arr)
{
	size_t	len;

	len = 0;
	while (arr && *arr && **arr && *(arr + len))
		len++;
	return (len);
}
