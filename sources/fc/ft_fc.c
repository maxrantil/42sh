/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:41:05 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/20 15:09:05 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	fc_init_flags(t_fc *fc)
{
	fc->l = false;
	fc->r = false;
	fc->s = false;
	fc->e = false;
	fc->n = false;
	fc->flags = 0;
	fc->start = 0;
	fc->end = 0;
	fc->filename = NULL;
}

static bool	validate_input(char ***cmd, t_fc *fc)
{
	int		i;
	int		h;

	i = fc->flags;
	if (fc->e)
		i++;
	h = i;
	while (!fc->s && (*cmd)[i] && i < (h + 2))
	{
		if (!ft_isdigit(*(*cmd)[i]) && (*(*cmd)[i] != '-'))
			return (false);
		i++;
	}
	return (true);
}

int	ft_fc(t_shell *sh, char ***cmd)
{
	t_fc	fc;
	int		ret;

	fc_init_flags(&fc);
	if (fc_get_flags(&fc, *cmd) == -1)
		return (0);
	ret = 0;
	if (fc.e && !(*cmd)[fc.flags])
		return (fc_usage('e', "option requires an argument"));
	if (!validate_input(cmd, &fc))
		return (fc_print_error(5));
	if (fc.s && !fc.e)
		return (fc_s_flag(sh, &fc, cmd));
	else if (!fc.l)
		ret = fc_no_flag_or_e_flag(sh, &fc, cmd);
	else if (fc.l)
	{
		if (fc.e)
			fc.flags++;
		return (fc_list_flags(sh, &fc, cmd));
	}
	return (ret);
}
