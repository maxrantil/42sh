/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_list_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:09:40 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 18:15:38 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	print_ell_only(t_shell *sh, t_fc *fc)
{
	while (++fc->start < fc->end - 1)
		ft_printf("%-8d %s\n", fc->start + 1, sh->term->history_arr[fc->start]);
}

static void	print_n_ell(t_shell *sh, t_fc *fc)
{
	while (++fc->start < fc->end - 1)
		ft_printf("\t %s\n", sh->term->history_arr[fc->start]);
}

static void	print_r_ell(t_shell *sh, t_fc *fc)
{
	while (--fc->end && fc->start < fc->end)
		ft_printf("%-8d %s\n", fc->end, sh->term->history_arr[fc->end - 1]);
}

static void	print_nr_ell(t_shell *sh, t_fc *fc)
{
	while (--fc->end && fc->start < fc->end)
		ft_printf("\t %s\n", sh->term->history_arr[fc->end - 1]);
}

int	fc_list_flags(t_shell *sh, t_fc *fc, char ***cmd)
{
	fc->end = sh->term->history_size;
	fc->start = fc_lflag_get_start_and_end(sh, fc, cmd);
	if (!fc->n && !fc->r)
		print_ell_only(sh, fc);
	else if (fc->n && !fc->r)
		print_n_ell(sh, fc);
	else if (fc->r && !fc->n)
		print_r_ell(sh, fc);
	else if (fc->r && fc->n)
		print_nr_ell(sh, fc);
	return (0);
}
