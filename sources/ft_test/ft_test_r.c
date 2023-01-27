/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:26:07 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 09:26:13 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

//True if file exists and is readable.
int	ft_test_r(char **arg)
{
	int		not;

	not = ft_test_is_not(arg);
	if (not && access(arg[3], R_OK) == 0)
		return (1);
	else if (access(arg[2], R_OK) == 0)
		return (0);
	return (ft_test_not_return_last(not));
}
