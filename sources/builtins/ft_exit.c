/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:23:30 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/02 15:49:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It exits the shell
 *
 * @param sh The session struct.
 * @param status The exit status of the shell.
 */
void	ft_exit(t_shell *sh, int status)
{
	sh->exit_stat = status;
	ft_printf("{RED}exit{RESET}\n");
	ft_history_write_to_file(sh->term);
	ft_raw_disable(sh->orig_termios);
	if (sh->term->clipboard.buff)
		ft_strdel(&sh->term->clipboard.buff);
	shell_end_cycle(sh);
	hash_free(sh->ht);
	close_all_bg_processes(sh);
	ft_strdel(&sh->terminal);
	exit(status);
}
