/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_is_binary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:31:13 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/27 19:13:36 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
	!=, -eq, -ne, -ge, -lt, -le, =
*/
int	ft_test_is_binary(char *str)
{
	return (ft_strequ(str, "!=") || ft_strequ(str, "-eq") \
		|| ft_strequ(str, "-ne") || ft_strequ(str, "-ge") \
		|| ft_strequ(str, "-gt") \
		|| ft_strequ(str, "-lt") || ft_strequ(str, "-le") \
		|| ft_strequ(str, "="));
}
