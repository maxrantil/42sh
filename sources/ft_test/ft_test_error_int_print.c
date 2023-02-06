/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_error_int_print.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:27:42 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/26 15:29:29 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	ft_test_error_int_print(char *arg)
{
	ft_putstr_fd("42sh: test: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": integer expression expected", 2);
	return (2);
}
