/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_overwrite_fc_cmd_with_prev_cmd.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:14:36 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/19 17:31:45 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	fc_overwrite_fc_cmd_with_prev_cmd(t_session *sesh, char ***cmd, int y)
{
	if (cmd)
		ft_freeda((void ***)cmd, calc_chptr(*cmd));
	*cmd = \
	ft_strsplit(sesh->term->history_arr[sesh->term->history_size - y], ' ');
	if (!*cmd)
		fc_print_error(3);
}
