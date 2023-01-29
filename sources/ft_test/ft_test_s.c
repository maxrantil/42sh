/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:25:23 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 11:39:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// True if file exists and has a size greater than zero.
int	ft_test_s(char **arg)
{
	struct stat	file_info;
	char		*filepath;
	int			not;

	not = ft_test_is_not(arg);
	filepath = ft_test_get_file_path(arg, not);
	if (stat(filepath, &file_info) != 0)
	{
		ft_strdel(&filepath);
		return (ft_test_not_return_last(not));
	}
	ft_strdel(&filepath);
	if (file_info.st_size > 0)
	{
		if (not)
			return (1);
		return (0);
	}
	return (ft_test_not_return_last(not));
}
