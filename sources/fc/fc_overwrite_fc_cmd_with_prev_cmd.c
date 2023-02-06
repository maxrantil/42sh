/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_overwrite_fc_cmd_with_prev_cmd.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:14:36 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/26 09:56:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	fc_overwrite_fc_cmd_with_prev_cmd(t_shell *sh, char ***cmd, int y)
{
	if (cmd)
		ft_freeda((void ***)cmd, calc_chptr(*cmd));
	*cmd = \
	ft_strsplit(sh->term->history_arr[sh->term->history_size - y], ' ');
	if (!*cmd)
		fc_print_error(3);
}
