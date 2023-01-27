/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_error_check_for_no_flag_or_e_flag.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:26:13 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 16:26:27 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	check_if_valid_size(t_shell *sh, int arg)
{
	if (arg > (int)sh->term->history_size \
		|| (arg * -1) > (int)sh->term->history_size)
	{
		return (1);
	}
	return (0);
}

int	fc_error_check_for_no_flag_or_e_flag(t_shell *sh, \
t_fc *fc, char ***cmd)
{
	int		arg1;
	int		arg2;

	if ((*cmd)[1 + fc->e] && !(*cmd)[2 + fc->e])
	{
		arg1 = ft_atoi((*cmd)[1 + fc->e]);
		if (check_if_valid_size(sh, arg1))
			return (fc_print_error(6));
	}
	else if ((*cmd)[1 + fc->e] && (*cmd)[2 + fc->e])
	{
		arg1 = ft_atoi((*cmd)[1 + fc->e]);
		arg2 = ft_atoi((*cmd)[2 + fc->e]);
		if (check_if_valid_size(sh, arg1) \
			|| check_if_valid_size(sh, arg2))
			return (fc_print_error(6));
	}
	return (1);
}
