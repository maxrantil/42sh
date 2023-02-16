/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:41:05 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/15 16:51:59by mbarutel         ###   ########.fr       */
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
}

static bool	validate_input(char ***cmd, t_fc *fc)
{
	int		i;
	int		j;

	i = fc->flags;
	while ((*cmd)[i])
	{
		j = 0;
		while ((*cmd)[i][j])
		{
			if (!ft_isdigit((*cmd)[i][j]) && ((*cmd)[i][j] != '-' && !j))
				return (false);
			j++;
		}		
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
		return (-1);
	ret = 0;
	if (fc.e && !(*cmd)[fc.flags])
		return (fc_usage("-e: option requires an argument"));
	if (fc.s && !fc.e)
		return (fc_s_flag(sh, &fc, cmd));
	else if (fc.e && !fc.l)
		ret = fc_no_flag_or_e_flag(sh, &fc, cmd);
	else if (fc.l)
	{
		if (fc.e)
			fc.flags++;
		if (!validate_input(cmd, &fc))
			return (fc_usage("invalid input"));
		return (fc_list_flags(sh, &fc, cmd));
	}
	return (ret);
}
