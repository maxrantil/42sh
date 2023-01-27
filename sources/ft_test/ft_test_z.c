/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_z.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:23:35 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 11:16:22 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// True if the length of string is zero.
int	ft_test_z(char **arg)
{
	int		not;

	not = ft_test_is_not(arg);
	if (not && ft_strlen(arg[3]) == 0)
		return (1);
	else if (ft_strlen(arg[2]) == 0)
		return (0);
	return (ft_test_not_return_last(not));
}
