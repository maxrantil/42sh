
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_check_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:43:22 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/13 14:25:48 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	int_check_validity(char *arg, char *prog)
{
	long		arg_long;
	int			len;

	arg_long = ft_atol(arg);
	len = ft_intlen(arg_long);
	if (!ft_isdigit_loop(arg) || len > 10 \
		|| arg_long < INT_MIN || arg_long > INT_MAX)
		return (ft_prog_error_int_print(arg, prog));
	return (0);
}
