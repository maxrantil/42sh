/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_no_flag_or_e_flag.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:35:13 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/13 13:31:50 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*get_editor(t_fc *fc, char **env)
{
	char	*editor;

	fc->e = 0;
	editor = search_bin(getenv("FCEDIT"), env);
	if (!editor)
		editor = search_bin(getenv("EDITOR"), env);
	if (!editor)
		editor = search_bin("vim", env);
	if (!editor)
		editor = search_bin("vi", env);
	if (!editor)
		editor = search_bin("ed", env);
	if (!editor)
		return (NULL);
	return (editor);
}

static int	fc_read_file(t_fc *fc, char **ret_cmd)
{
	int		fd;
	char	*new_cmd;

	new_cmd = NULL;
	fd = open(fc->filename[1], O_RDONLY);
	if (fd == -1)
		return (fc_print_error(2));
	while (get_next_line(fd, &new_cmd) > 0)
	{
		if (!(*ret_cmd))
			*ret_cmd = ft_strdup(new_cmd);
		else
		{
			*ret_cmd = ft_strupdate(*ret_cmd, ";");
			*ret_cmd = ft_strupdate(*ret_cmd, new_cmd);
		}
		ft_strdel(&new_cmd);
	}
	ft_strdel(&new_cmd);
	close(fd);
	if (!(*ret_cmd))
		return (0);
	return (1);
}

static void	fc_overwrite_history(t_shell *sh, char *ret_cmd)
{
	char	**args;
	int		i;

	ft_strdel(&sh->term->history_arr[sh->term->history_size - 1]);
	sh->term->history_size--;
	args = ft_strsplit(ret_cmd, ';');
	i = 0;
	while (args[i])
		ft_history_add_command(sh->term, args[i++]);
	ft_freeda((void ***)&args, calc_chptr(args));
}

static int	empty_in_editor(t_shell *sh, t_fc *fc)
{
	fc_free(fc);
	ft_strdel(&sh->term->history_arr[sh->term->history_size - 1]);
	sh->term->history_size--;
	return (0);
}

int	fc_no_flag_or_e_flag(t_shell *sh, t_fc *fc, char ***cmd)
{
	char	*editor;

	if (!(*cmd)[fc->flags] || fc_no_flags(fc))
		editor = get_editor(fc, sh->env);
	else
	{
		editor = search_bin((*cmd)[fc->flags], sh->env);
		if (ft_strnequ((*cmd)[fc->flags + 1], "--", 2))
			fc->flags++;
	}
	if (!editor)
		return (fc_print_error(5));
	fc_open_editor(editor, sh, fc, cmd);
	if (!fc->filename)
		return (0);
	fc->ret_cmd = NULL;
	if (!fc_read_file(fc, &fc->ret_cmd))
		return (empty_in_editor(sh, fc));
	fc_overwrite_history(sh, fc->ret_cmd);
	fc_build_and_execute_new_tree(sh, fc);
	return (0);
}
