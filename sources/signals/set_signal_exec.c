/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:24:56 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/30 16:12:36 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	set_signal_exec(void)
{
	int	sig;

	sig = -1;
	while (++sig < 32)
		signal(sig, signal_exec);
	signal(SIGCHLD, child_exit);
}
