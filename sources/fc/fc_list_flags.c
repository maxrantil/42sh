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

static void	print_ell_only(t_shell *sh, int start)
{
	while (++start < (int)sh->term->history_size - 1)
		ft_printf("%-8d %s\n", start + 1, sh->term->history_arr[start]);
}

static void	print_n_ell(t_shell *sh, int start)
{
	while (++start < (int)sh->term->history_size - 1)
		ft_printf("\t %s\n", sh->term->history_arr[start]);
}

static void	print_r_ell(t_shell *sh, int start)
{
	while (--start && start > (int)sh->term->history_size - FC_LEN)
		ft_printf("%-8d %s\n", start, sh->term->history_arr[start - 1]);
}

static void	print_nr_ell(t_shell *sh, int start)
{
	while (--start && start > (int)sh->term->history_size - FC_LEN)
		ft_printf("\t %s\n", sh->term->history_arr[start - 1]);
}

// fix for empy history? fc -l in fist line prints it out if its empty
int	fc_list_flags(t_shell *sh, char ***cmd)
{
	int		start;
	size_t	hold;

	hold = sh->term->history_size;
	start = fc_get_start_for_lists(sh, cmd);
	if (!ft_strchr((*cmd)[1], 'n') && !ft_strchr((*cmd)[1], 'r'))
		print_ell_only(sh, start);
	else if (ft_strchr((*cmd)[1], 'n') && !ft_strchr((*cmd)[1], 'r'))
		print_n_ell(sh, start);
	if (sh->term->history_size > FC_LEN)
		start += FC_LEN;
	else
		start = sh->term->history_size;
	if (ft_strchr((*cmd)[1], 'r') && !ft_strchr((*cmd)[1], 'n'))
		print_r_ell(sh, start);
	else if (ft_strchr((*cmd)[1], 'r') && ft_strchr((*cmd)[1], 'n'))
		print_nr_ell(sh, start);
	if (hold != sh->term->history_size)
		sh->term->history_size = hold;
	return (0);
}
