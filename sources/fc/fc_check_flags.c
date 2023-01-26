/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:20:17 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/26 10:40:35 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	update_history(t_shell *sh, char ***cmd)
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

static void fc_use_last_match(t_shell *sh, char ***cmd, int y)
{
	ft_freeda((void ***)cmd, calc_chptr(*cmd));
	*cmd = \
	ft_strsplit(sh->term->history_arr[y], ' ');
	if (!*cmd)
		fc_print_error(3);
	update_history(sh, cmd);
}

static int	find_matching(t_shell *sh, char *str, char ***cmd)
{
	int		y;
	int		x;
	int		len;

	y = sh->term->history_size - 1;
	len = ft_strlen(str);
	while (y > 0)
	{
		x = 0;
		while (sh->term->history_arr[y][x] && str[x] && sh->term->history_arr[y][x] == str[x])
			x++;
		if (x == len)
		{
			fc_use_last_match(sh, cmd, y);
			break ;
		}
		y--;
	}
	if (y == 0)
		return (fc_print_error(5));
	return (1);
}

static int	fc_s_only(t_shell *sh, char ***cmd)
{
	ft_strdel(&sh->term->history_arr[sh->term->history_size - 1]);
	sh->term->history_arr[sh->term->history_size - 1] = \
	ft_strdup(sh->term->history_arr[sh->term->history_size - 2]);
	ft_freeda((void ***)cmd, calc_chptr(*cmd));
	ft_putendl(sh->term->history_arr[sh->term->history_size - 2]);
	*cmd = \
	ft_strsplit(sh->term->history_arr[sh->term->history_size - 2], ' ');
	if (!*cmd)
		fc_print_error(3);
	return (1);
}

static void	change_all_occurrences(char ***tmp_cmd, char *needle, char *change_to)
{
	int		i;
	char	*begin;
	char	*end;

	i = 0;
	while ((*tmp_cmd)[i])
	{
		while (ft_strstr((*tmp_cmd)[i], needle))
		{
			begin = ft_strsub((*tmp_cmd)[i], 0, ft_strstr((*tmp_cmd)[i], needle) - (*tmp_cmd)[i]);
			end = ft_strsub((*tmp_cmd)[i], ft_strstr((*tmp_cmd)[i], needle) - (*tmp_cmd)[i] + \
			ft_strlen(needle), ft_strlen((*tmp_cmd)[i]) - ft_strlen(needle) - ft_strlen(begin));
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
	*cmd = (char **)malloc(sizeof(char *) * calc_chptr(*tmp_cmd) + sizeof(char *));
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

static int	fc_s_change(t_shell *sh, char ***cmd)
{
	int		i;
	char	*change_to;
	char	*needle;
	char 	**tmp_cmd;

	tmp_cmd = NULL;
	fc_overwrite_fc_cmd_with_prev_cmd(sh, &tmp_cmd, 2);
	i = 2;
	while ((*cmd)[i] && ft_strchr((*cmd)[i], '='))
	{
		change_to = ft_strdup(ft_strchr((*cmd)[i], '=') + 1);
		needle = ft_strsub((*cmd)[i], 0, ft_strchr((*cmd)[i], '=') - (*cmd)[i]);
		change_all_occurrences(&tmp_cmd, needle, change_to);
		ft_strdel(&needle);
		ft_strdel(&change_to);
		i++;
	}
	update_history(sh, &tmp_cmd);
	update_cmd(cmd, &tmp_cmd);
	return (1);
}

static int	fc_s_flag(t_shell *sh, char ***cmd) // make a loop here and look for arguments after
{
	int i;

	if (*(cmd) && (*cmd)[1] && !(*cmd)[2])
		return (fc_s_only(sh, cmd));
	i = 2;
	while ((*cmd)[i] && ft_strchr((*cmd)[i], '='))
		i++;
	if ((*cmd)[i])
		return (find_matching(sh, (*cmd)[i], cmd));
	else if (ft_strchr((*cmd)[2], '='))
		return (fc_s_change(sh, cmd));
	return (0);
}

static int	null_check_first(t_shell *sh, char *cmd)
{
	int start;

	if (ft_atoi(cmd) == 0)
	{
		start = sh->term->history_size - 3;
		sh->term->history_size -= 1;
	}
	else
		start = ft_atoi(cmd) - 2;
	if (start < -1)
	{
		start = sh->term->history_size + start;
		if (start < 0)
			start = -1;
	}
	return (start);
}

static int	null_check_last(t_shell *sh, char *cmd)
{
	int last;

	if (ft_atoi(cmd) == 0)
		last = sh->term->history_size;
	else
		last = ft_atoi(cmd) + 1;
	if (last <= 0)
		last = sh->term->history_size;
	return (last);
}

static int	get_start(t_shell *sh, char ***cmd)
{
	int start;

	if ((*cmd)[0] && (*cmd)[1] && (*cmd)[2] && !(*cmd)[3])
		start = null_check_first(sh, (*cmd)[2]);
	else if ((*cmd)[0] && (*cmd)[1] && (*cmd)[2] && (*cmd)[3])
	{
		start = null_check_first(sh, (*cmd)[2]);
		sh->term->history_size = null_check_last(sh, (*cmd)[3]);
	}
	else if (sh->term->history_size > FC_LEN)
		start = sh->term->history_size - FC_LEN;
	else
		start = -1;
	return (start);
}

static void print_ell_only(t_shell *sh, int start)
{
	while (++start < (int)sh->term->history_size - 1)
		ft_printf("%-8d %s\n", start + 1, sh->term->history_arr[start]);
}

static void print_n_ell(t_shell *sh, int start)
{
	while (++start < (int)sh->term->history_size - 1)
		ft_printf("\t %s\n", sh->term->history_arr[start]);
}

static void print_r_ell(t_shell *sh, int start)
{
	while (--start && start > (int)sh->term->history_size - FC_LEN)
		ft_printf("%-8d %s\n", start, sh->term->history_arr[start - 1]);
}

static void print_nr_ell(t_shell *sh, int start)
{
	while (--start && start > (int)sh->term->history_size - FC_LEN)
		ft_printf("\t %s\n", sh->term->history_arr[start - 1]);
}

//add [fist] [last] option to the call
static int	fc_list_flag(t_shell *sh, char ***cmd) // fix for empy history? fc -l in fist line prints it out if its empty
{
	int 	start;
	size_t	hold;

	hold = sh->term->history_size;
	start = get_start(sh, cmd);
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

static int	loop_flags(t_shell *sh, char ***cmd)
{
	int i;

	i = 1;
	while ((*cmd)[1][i])
	{
		if ((*cmd)[1][i] == 's')
			return (fc_s_flag(sh, cmd));
		else
			return (fc_list_flag(sh, cmd));
	}
	return (0);
}

int	fc_check_flags(t_shell *sh, char ***cmd)
{
	int i;

	if (*cmd && ft_strnequ((*cmd)[1], "-", 1))
	{
		i = 1;
		while ((*cmd)[1][i])
		{
			if ((*cmd)[1][i] != 's' && (*cmd)[1][i] != 'l' \
				&& (*cmd)[1][i] != 'n' && (*cmd)[1][i] != 'r')
			{
				ft_putstr_fd("42sh: fc: invalid option", 2);
				ft_putstr_fd("fc: usage: fc [-e ename] [-lnr] ", 2);
				ft_putendl_fd("[first] [last] or fc -s [pat=rep] [command]", 2);
				return (0);
			}
			i++;
		}
	}
	return (loop_flags(sh, cmd));
}
