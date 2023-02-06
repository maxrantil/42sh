/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:41:05 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/03 15:44:37 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/* static int	check_if_valid_input(t_fc *fc, char ***cmd)
{
	if ((*cmd && !(*cmd)[1 + fc->e]) \
		|| (*cmd && (*cmd)[1 + fc->e] \
		&& (*cmd)[1 + fc->e][0] == '-' \
		&& ft_isdigit((*cmd)[1 + fc->e][1])) \
		|| (*cmd && (*cmd)[1 + fc->e] && ft_isdigit((*cmd)[1 + fc->e][0])) \
		|| (*cmd && fc->e))
	{
		return (1);
	}
	return (0);
} */

static void fc_init_flags(t_fc *fc)
{
	fc->l = false;
	fc->r = false;
	fc->s = false;
	fc->e = 0;
	fc->n = false;
	fc->flags = 0;
	fc->start = 0;
	fc->end = 0;
}

int	ft_fc(t_shell *sh, char ***cmd)
{
	t_fc	fc;
	int		ret;

	fc_init_flags(&fc);
	if (!fc_get_flags(&fc, *cmd))
		return (0);
	ret = 0;
	if (fc.s && !ft_strnequ((*cmd)[1], "-e", 2))
		return (fc_s_flag(sh, &fc, cmd));
	else if (fc.e || fc_no_flags(&fc))
	{
		// if (fc_error_check_for_no_flag_or_e_flag(sh, &fc, cmd))
			ret = fc_no_flag_or_e_flag(sh, &fc, cmd);

	}
	else if (fc.l)
		return (fc_list_flags(sh, &fc, cmd));
	return (ret);
}
