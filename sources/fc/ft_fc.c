/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:41:05 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/13 13:26:28 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	fc_init_flags(t_fc *fc)
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
		return (-1);
	ret = 0;
	if (fc.s && !ft_strnequ((*cmd)[1], "-e", 2))
		return (fc_s_flag(sh, &fc, cmd));
	else if (fc.e || fc_no_flags(&fc))
		ret = fc_no_flag_or_e_flag(sh, &fc, cmd);
	else if (fc.l)
		return (fc_list_flags(sh, &fc, cmd));
	return (ret);
}
