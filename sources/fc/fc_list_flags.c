/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_list_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:09:40 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/15 13:32:39 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	print_low_to_high(t_shell *sh, t_fc *fc)
{
	while (fc->start <= fc->end)
	{
		if (fc->l && !fc->n)
			ft_printf("%-8d %s\n", fc->start + 1, sh->term->history_arr[fc->start]);
		else if (fc->n)
			ft_printf("\t %s\n", sh->term->history_arr[fc->start]);
		++fc->start;
	}
}

static void	print_high_to_low(t_shell *sh, t_fc *fc)
{
	while (fc->start >= fc->end)
	{
		if (fc->l && !fc->n)
			ft_printf("%-8d %s\n", fc->start + 1, sh->term->history_arr[fc->start]);
		else if (fc->n)
			ft_printf("\t %s\n", sh->term->history_arr[fc->start]);
		--fc->start;
	}
}

static void	swap_end_start(t_fc *fc)
{
	fc->start ^= fc->end;
	fc->end ^= fc->start;
	fc->start ^= fc->end;
}

int	fc_list_flags(t_shell *sh, t_fc *fc, char ***cmd)
{
	fc_get_start_and_end(sh, fc, cmd);
	if (fc->r && fc->start < fc->end)
		swap_end_start(fc);
	if (fc->start <= fc->end)
		print_low_to_high(sh, fc);
	else
		print_high_to_low(sh, fc);
	return (0);
}
