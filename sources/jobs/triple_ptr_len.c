/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triple_ptr_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:21:41 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/01 14:22:17 by mbarutel         ###   ########.fr       */
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
size_t   triple_ptr_len(char ***arr)
{
    size_t len;

    len = 0;
    while (*(arr + len))
        len++;
    return (len);
}
