/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_empty_str_array.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:28:22 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/23 15:06:23 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	**ft_create_empty_str_array(int size)
{
	char	**arr;

	arr = (char **) malloc(sizeof(char *) * (size + 1));
	if (!arr)
		exit(2);
	while (size >= 0)
		arr[size--] = NULL;
	return (arr);
}
