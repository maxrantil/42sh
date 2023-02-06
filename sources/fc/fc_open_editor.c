/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_open_editor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:41:27 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 14:05:54 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	init_filename(char ***filename, char *editor)
{
	(*filename) = (char **)malloc(sizeof(char *) * 3);
	if (!(*filename))
	{
		ft_putstr_fd("42sh: Error malloc, init_filename() from ft_fc().", 2);
		exit(1);
	}
	(*filename)[0] = editor;
	(*filename)[1] = ft_strdup("/tmp/ft_fc");
	(*filename)[2] = NULL;
}

static void	print_to_file(t_shell *sh, t_fc *fc, char ***cmd, int fd)
{
	if (!fc_get_start_and_end(sh, fc, cmd))
		return ;
	if (fc->start <= fc->end)
	{
		while (++fc->start < fc->end)
			ft_putendl_fd(sh->term->history_arr[fc->start], fd);
	}
	else
	{
		while (--fc->start > fc->end)
			ft_putendl_fd(sh->term->history_arr[fc->start], fd);
	}
}

void	fc_open_editor(char *editor, t_shell *sh, t_fc *fc, char ***cmd)
{
	int		fd;

	init_filename(&fc->filename, editor);
	fd = open(fc->filename[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		fc_print_error(2);
		return ;
	}
	print_to_file(sh, fc, cmd, fd);
	if (fork_wrap() == 0)
	{
		if (execve(editor, fc->filename, sh->env) == -1)
			ft_putendl_fd("42sh: Error execve, fc_open_editor() from ft_fc().", 2);
		exit(1);
	}
	wait(0);
	close(fd);
}
