/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:21:42 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/11 18:23:10 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	exit_error(t_shell *sh, int status, char *msg)
{
	ft_putendl_fd(msg, 2);
	ft_history_write_to_file(sh->term);
	ft_raw_disable(sh->orig_termios);
	if (sh->term->clipboard.buff)
		ft_strdel(&sh->term->clipboard.buff);
	shell_end_cycle(sh);
	exit(status);
}
