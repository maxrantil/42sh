/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:24:04 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 11:16:26 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

//	True if file exists and is executable.  True indicates only
//	that the execute flag is on.  If file is a directory, true
//	indicates that file can be searched.
int	ft_test_x(char **arg)
{
	int		not;

	not = ft_test_is_not(arg);
	if (not && access(arg[3], X_OK) == 0)
		return (1);
	else if (access(arg[2], X_OK) == 0)
		return (0);
	return (ft_test_not_return_last(not));
}
