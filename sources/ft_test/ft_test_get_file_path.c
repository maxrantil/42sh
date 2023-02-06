/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_get_file_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:22:20 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 11:56:39 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*ft_test_get_file_path(char **arg, int not)
{
	char		filepath[PATH_MAX];
	char		*ret_path;
	int			argc;

	ret_path = NULL;
	argc = ft_arrlen(arg);
	if (argc > (2 + not) && arg[2 + not][0] != '/')
	{
		getcwd(filepath, sizeof(filepath));
		ret_path = ft_strjoin_three(filepath, "/", arg[2 + not]);
	}
	else if (argc > (2 + not))
		ret_path = ft_strdup(arg[2 + not]);
	return (ret_path);
}
