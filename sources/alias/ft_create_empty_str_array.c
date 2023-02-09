/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_empty_str_array.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:28:22 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/06 16:47:52 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "libft.h"

char	**ft_create_empty_str_array(int size)
{
	char	**arr;

	arr = (char **) malloc(sizeof(char *) * (size + 1));
	if (!arr)
		exit(2);
		// ft_exit_error("ft_create_empty_str_array.c", 47);
	while (size >= 0)
		arr[size--] = NULL;
	return (arr);
}
