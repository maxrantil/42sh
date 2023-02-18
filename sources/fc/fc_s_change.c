/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_s_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:21:29 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 18:25:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	change_all_occurrences(char ***tmp_cmd, char *needle, \
char *change_to)
{
	int		i;
	char	*begin;
	char	*end;

	i = 0;
	while ((*tmp_cmd)[i])
	{
		while (ft_strstr((*tmp_cmd)[i], needle))
		{
			begin = ft_strsub((*tmp_cmd)[i], 0, \
			ft_strstr((*tmp_cmd)[i], needle) - (*tmp_cmd)[i]);
			end = ft_strsub((*tmp_cmd)[i], ft_strstr((*tmp_cmd)[i], \
			needle) - (*tmp_cmd)[i] + ft_strlen(needle), \
			ft_strlen((*tmp_cmd)[i]) - ft_strlen(needle) - ft_strlen(begin));
			ft_strdel(&(*tmp_cmd)[i]);
			(*tmp_cmd)[i] = ft_strjoin_three(begin, change_to, end);
			ft_strdel(&begin);
			ft_strdel(&end);
		}
		i++;
	}
}

static void	update_cmd(char ***cmd, char ***tmp_cmd)
{
	size_t		i;

	ft_freeda((void ***)cmd, calc_chptr(*cmd));
	*cmd = (char **)malloc(sizeof(char *) * (calc_chptr(*tmp_cmd) + 1));
	if (!*cmd)
		fc_print_error(3);
	(*cmd)[calc_chptr(*tmp_cmd)] = NULL;
	i = 0;
	while (i < calc_chptr(*tmp_cmd))
	{
		(*cmd)[i] = ft_strdup((*tmp_cmd)[i]);
		i++;
	}
	ft_freeda((void ***)tmp_cmd, calc_chptr(*tmp_cmd));
}

int	fc_s_change(t_shell *sh, t_fc *fc, char ***cmd, int y)
{
	int		i;
	char	*change_to;
	char	*needle;
	char	**tmp_cmd;

	tmp_cmd = NULL;
	fc_overwrite_fc_cmd_with_prev_cmd(sh, &tmp_cmd, y);
	i = fc->flags;
	while ((*cmd)[i] && ft_strchr((*cmd)[i], '='))
	{
		change_to = ft_strdup(ft_strchr((*cmd)[i], '=') + 1);
		needle = ft_strsub((*cmd)[i], 0, ft_strchr((*cmd)[i], '=') - (*cmd)[i]);
		change_all_occurrences(&tmp_cmd, needle, change_to);
		ft_strdel(&needle);
		ft_strdel(&change_to);
		i++;
	}
	fc_update_history(sh, &tmp_cmd);
	update_cmd(cmd, &tmp_cmd);
	return (1);
}
