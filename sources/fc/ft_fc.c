/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:41:05 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/26 10:12:15 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

//add to libft
static char	*ft_strupdate(char *s1, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (!ret)
		return (NULL);
	ft_strdel(&s1);
	return (ret);
}

static char	*get_editor(char **env)
{
	char *editor;

	editor = getenv("FCEDIT");
	if (!editor)
		editor = getenv("EDITOR");
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

//implement for too low number and too high number
static int	get_start_and_end(t_shell *sh, t_fc *fc, char ***cmd)
{
	if (!(*cmd)[1 + fc->e])
	{
		fc->start = (int)sh->term->history_size - 3;
		fc->end = (int)sh->term->history_size - 1;
	}
	else if ((*cmd)[1 + fc->e] && !(*cmd)[2 + fc->e])
	{
		if ((*cmd)[1 + fc->e][0] == '-')
		{
			fc->start = (int)sh->term->history_size + ft_atoi((*cmd)[1 + fc->e]) - 2;
			fc->end = fc->start + 2;
		}
		else
		{
			fc->start = ft_atoi((*cmd)[1 + fc->e]) - 2;
			fc->end = ft_atoi((*cmd)[1 + fc->e]);
		}
	}
	else if ((*cmd)[1 + fc->e] && (*cmd)[2 + fc->e])
	{
		if ((*cmd)[1 + fc->e][0] == '-')
			fc->start = (int)sh->term->history_size + ft_atoi((*cmd)[1 + fc->e]);
		else
			fc->start = ft_atoi((*cmd)[1 + fc->e]) - 2;
		if ((*cmd)[2 + fc->e][0] == '-')
		{
			if ((*cmd)[1 + fc->e][0] == '-')
				fc->end = (int)sh->term->history_size + ft_atoi((*cmd)[2 + fc->e]) - 2;
			else
				fc->end = (int)sh->term->history_size + ft_atoi((*cmd)[2 + fc->e]) - 1;
		}
		else
		{
			if ((*cmd)[1 + fc->e][0] == '-')
				fc->end = ft_atoi((*cmd)[2 + fc->e]) - 2;
			else
				fc->end = ft_atoi((*cmd)[2 + fc->e]);
		}
	}
	else
		return (0);
	return (1);
}

static void	print_to_file(t_shell *sh, t_fc *fc, char ***cmd, int fd)
{
	if (!get_start_and_end(sh, fc, cmd))
		return ;
	if (fc->start <= fc->end) // is equal sign good here?
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

static void	open_editor(char *editor, t_shell *sh, t_fc *fc, char ***cmd)
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
		execve(editor, fc->filename, sh->env);
		exit(1);
	}
	wait(0);
	close(fd);
}

static int	read_file(t_fc *fc, char **ret_cmd)
{
	int		fd;
	char	*new_cmd;

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
	return (1);
}

static void	overwrite_history(t_shell *sh, char *ret_cmd)
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

static int	no_flag_or_e_flag(t_shell *sh, t_fc *fc, char ***cmd)
{
	char	*editor;

	if ((*cmd && (*cmd)[1] && ft_strnequ((*cmd)[1], "-e", 2) && (*cmd)[2]))
		editor = search_bin((*cmd)[2], sh->env);
	else
		editor = get_editor(sh->env);
	if (!editor)
		return (fc_print_error(1));
	open_editor(editor, sh, fc, cmd);
	if (!fc->filename)
		return (0);
	fc->ret_cmd = NULL;
	if (!read_file(fc, &fc->ret_cmd))
		return (0);
	ft_freeda((void ***)cmd, calc_chptr(*cmd));
	overwrite_history(sh, fc->ret_cmd);

	char		*new;
	t_treenode	*head;
	t_token 	*tokens;

	sh->term->fc_flag = true;
	tokens = NULL;
	new = ft_strtrim(fc->ret_cmd); //do we need to implement heredoc aswell here?
	ft_freeda((void ***)&fc->filename, calc_chptr(fc->filename));
	tokens = chop_line(new, tokens, 1);
	head = build_tree(&tokens);
	if (head && ((t_semicolon *)head)->left)
		exec_tree(head, &sh->env, sh->terminal, sh);
	free_node(head);
	free_tokens(&tokens);
	ft_strdel(&fc->ret_cmd);
	return (0);
}

int	ft_fc(t_shell *sh, char ***cmd)
{
	t_fc 	fc;
	int		ret;

	fc.e = 0;
	if ((*cmd)[1] && ft_strnequ((*cmd)[1], "-e", 2))
		fc.e = 2;
	if ((*cmd && !(*cmd)[1 + fc.e]) \
		|| (*cmd && (*cmd)[1 + fc.e] && (*cmd)[1 + fc.e] && (*cmd)[1 + fc.e][0] == '-' && ft_isdigit((*cmd)[1 + fc.e][1])) \
		|| (*cmd && (*cmd)[1 + fc.e] && (*cmd)[1 + fc.e] && ft_isdigit((*cmd)[1 + fc.e][0])) \
		|| (*cmd && fc.e ))
	{
		if ((*cmd)[1 + fc.e] && !(*cmd)[2 + fc.e])
		{
			if (ft_atoi((*cmd)[1 + fc.e]) > (int)sh->term->history_size
				|| (ft_atoi((*cmd)[1 + fc.e]) * -1) > (int)sh->term->history_size)
			{
				ft_putendl_fd("42sh: fc: event not found", 2);
				return (0);
			}
		}
		else if ((*cmd)[1 + fc.e] && (*cmd)[2 + fc.e])
		{
			if (ft_atoi((*cmd)[1 + fc.e]) > (int)sh->term->history_size
				|| (ft_atoi((*cmd)[1 + fc.e]) * -1) > (int)sh->term->history_size
				|| ft_atoi((*cmd)[2 + fc.e]) > (int)sh->term->history_size
				|| (ft_atoi((*cmd)[2 + fc.e]) * -1) > (int)sh->term->history_size)
			{
				ft_putendl_fd("42sh: fc: event not found", 2);
				return (0);
			}
		}
		ret = no_flag_or_e_flag(sh, &fc, cmd);
	}
	else
		ret = fc_check_flags(sh, cmd);
	return (ret);
}
