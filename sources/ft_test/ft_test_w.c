/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_w.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:24:25 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 11:16:29 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

//	True if file exists and is writable.  True indicates only
//	that the write flag is on.  The file is not writable on a
//	read-only file system even if this test indicates true.
int	ft_test_w(char **arg)
{
	int		not;

	not = ft_test_is_not(arg);
	if (not && access(arg[3], W_OK) == 0)
		return (1);
	else if (access(arg[2], W_OK) == 0)
		return (0);
	return (ft_test_not_return_last(not));
}
