/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_update_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:23:39 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 18:23:47 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	fc_update_history(t_shell *sh, char ***cmd)
{
	int		i;
	char	*new_hist;

	ft_strdel(&sh->term->history_arr[sh->term->history_size - 1]);
	new_hist = ft_strnew(0);
	i = 0;
	while ((*cmd)[i])
	{
		ft_printf("%s", (*cmd)[i]);
		if ((*cmd)[i + 1])
			ft_printf(" ");
		new_hist = ft_strupdate(new_hist, (*cmd)[i]);
		if ((*cmd)[i + 1])
			new_hist = ft_strupdate(new_hist, " ");
		i++;
	}
	write(1, "\n", 1);
	sh->term->history_arr[sh->term->history_size - 1] = new_hist;
}
