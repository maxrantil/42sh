/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_check_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:43:22 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/17 16:44:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It checks if the argument is a valid integer
 *
 * @param arg the string to be checked
 * @param prog The name of the program.
 *
 * @return 0 if the argument is valid, and 1 if it is not.
 */
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
