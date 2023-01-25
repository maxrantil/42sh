/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_fail.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:38:50 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/16 13:16:28 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_freeda(void ***a, size_t row)
{
	unsigned int	i;

	i = -1;
	if (!a || !*a || !(*a)[0])
		return (1);
	while ((*a)[++i] && i < row)
		ft_strdel((char **)&(*a)[i]);
	ft_memdel((void **)a);
	return (1);
}

size_t	calc_chptr(char **arr)
{
	size_t	i;

	if (!arr || !arr[0])
		return (0);
	i = 0;
	while (arr[i])
		++i;
	return (i);
}

int	ms_exit(char **args, char ***environ_cp)
{
	int	status;

	status = 0;
	if (args[1])
		status = ft_atoi(args[1]);
	ft_freeda((void ***)&args, calc_chptr(args));
	ft_freeda((void ***)environ_cp, calc_chptr(*environ_cp));
	exit (status);
}

void	exe_fail(char **cmd, char **args, char ***env_cp)
{
	ft_err_print(NULL, args[0], "command not found", 2);
	ft_memdel((void **)cmd);
	ms_exit(args, env_cp);
}
