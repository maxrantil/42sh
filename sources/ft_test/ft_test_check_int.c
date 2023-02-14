/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_check_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:40:18 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/13 14:26:56 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	ft_test_check_int(char **arg, int not)
{
	if (not)
	{
		if (int_check_validity(arg[2], "test"))
			return (2);
		if (int_check_validity(arg[4], "test"))
			return (2);
	}
	else
	{
		if (int_check_validity(arg[1], "test"))
			return (2);
		if (int_check_validity(arg[3], "test"))
			return (2);
	}
	return (0);
}
