/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_equal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:18:10 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 09:18:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// True if the strings s1 and s2 are identical.
int	ft_test_equal(char **arg)
{
	int		not;

	not = ft_test_is_not(arg);
	if (not && ft_strequ(arg[2], arg[4]))
		return (1);
	else if (ft_strequ(arg[1], arg[3]))
		return (0);
	return (ft_test_not_return_last(not));
}
