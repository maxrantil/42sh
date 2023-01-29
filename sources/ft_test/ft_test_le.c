/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_le.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:18:48 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 09:18:54 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

//	True if the integer n1 is algebraically less than or equal
//	to the integer n2.
int	ft_test_le(char **arg)
{
	int		not;
	int		ret;

	not = ft_test_is_not(arg);
	ret = ft_test_check_int(arg, not);
	if (ret)
		return (ret);
	if (not && ft_atoi(arg[2]) <= ft_atoi(arg[4]))
		return (1);
	else if (ft_atoi(arg[1]) <= ft_atoi(arg[3]))
		return (0);
	return (ft_test_not_return_last(not));
}
