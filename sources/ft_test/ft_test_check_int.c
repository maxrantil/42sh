/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_check_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:40:18 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 19:17:29 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	check_validity(char *arg)
{
	long		arg_long;
	int			len;

	arg_long = ft_atol(arg);
	len = ft_intlen(arg_long);
	if (!ft_isdigit_loop(arg) || len > 10 \
		|| arg_long < INT_MIN || arg_long > INT_MAX)
		return (ft_test_error_int_print(arg));
	return (0);
}

int	ft_test_check_int(char **arg, int not)
{
	if (not)
	{
		if (check_validity(arg[2]))
			return (2);
		if (check_validity(arg[4]))
			return (2);
	}
	else
	{
		if (check_validity(arg[1]))
			return (2);
		if (check_validity(arg[3]))
			return (2);
	}
	return (0);
}
