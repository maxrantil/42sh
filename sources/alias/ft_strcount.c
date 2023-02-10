/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:58:04 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/06 16:48:09 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "../../libft/includes/libft.h"

void	ft_exit_error(char *msg, int ret);

int	ft_strcount(char *str, char target)
{
	int	i;
	int	found;

	if (!str)
		ft_exit_error("ft_strcount.c", 37);
	i = -1;
	found = 0;
	while (str[++i])
	{
		if (str[i] == target)
			found++;
	}
	return (found);
}
