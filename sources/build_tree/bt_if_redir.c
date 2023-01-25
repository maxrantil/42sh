/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_if_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:52:25 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/06 12:52:25 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_treenode	*init_redir(char *filepath,
		t_treenode *cmd, int close_fd, int open_flags)
{
	t_treenode	*redir;

	redir = ft_memalloc(sizeof(*redir));
	redir->type = REDIR;
	((t_redir *)redir)->type = REDIR;
	((t_redir *)redir)->cmd = cmd;
	((t_redir *)redir)->close_fd = close_fd;
	((t_redir *)redir)->filepath = filepath;
	((t_redir *)redir)->open_flags = open_flags;
	if (close_fd == 0)
		((t_redir *)redir)->rights = 0;
	else
		((t_redir *)redir)->rights = 0644;
	return (redir);
}

static int	redir_type(char *value)
{
	char	*type;
	char	*tmp;

	type = ft_strchr(value, '>');
	tmp = ft_strchr(value, '<');
	if (type && tmp)
		if (tmp < type)
			type = tmp;
	if (!type && tmp)
		type = tmp;
	if (ft_strstr(type, "<<<"))
		return (RE_IN_TRI);
	else if (ft_strstr(type, "<<"))
		return (RE_IN_TWO);
	else if (ft_strstr(type, "<"))
		return (RE_IN_ONE);
	else if (ft_strstr(type, ">>"))
		return (RE_OUT_TWO);
	else if (ft_strstr(type, ">"))
		return (RE_OUT_ONE);
	return (0);
}

t_treenode	*init_redir_wrap(char *filepath,
	t_treenode *cmd, int redir_type, int close_fd)
{
	if (close_fd < 0 && (redir_type == RE_IN_ONE
			|| redir_type == RE_IN_TWO || redir_type == RE_IN_TRI))
		close_fd = STDIN_FILENO;
	else if (close_fd < 0)
		close_fd = STDOUT_FILENO;
	if (redir_type == RE_IN_ONE)
		return (init_redir(filepath, cmd, close_fd, O_RDONLY));
	else if (redir_type == RE_OUT_ONE)
		return (init_redir(filepath, cmd, close_fd,
				O_CREAT | O_TRUNC | O_RDWR));
	else if (redir_type == RE_OUT_TWO)
		return (init_redir(filepath, cmd, close_fd,
				O_CREAT | O_APPEND | O_RDWR));
	return (NULL);
}

static void	make_child_for_prev(t_treenode **redir,
		char *dest, int redir_t, int close_fd)
{
	if ((*redir)->type == REDIR)
		((t_redir *)(*redir))->cmd = init_redir_wrap(dest,
				(((t_redir *)(*redir))->cmd), redir_t, close_fd);
	if ((*redir)->type == CLOSEFD)
		((t_closefd *)(*redir))->cmd = init_redir_wrap(dest,
				(((t_closefd *)(*redir))->cmd), redir_t, close_fd);
	if ((*redir)->type == AGGREGATION)
		((t_aggregate *)(*redir))->cmd = init_redir_wrap(dest,
				(((t_aggregate *)(*redir))->cmd), redir_t, close_fd);
	traverse_node(redir);
}

int	if_redir(t_token *tokens, t_treenode **redir, int i_tok, int cmd)
{
	int		redir_t;
	char	*dest;
	int		close_fd;

	close_fd = get_close_fd(tokens[i_tok].value);
	dest = get_file(ft_strchr(tokens[i_tok].value, '>'));
	if (!dest)
		dest = get_file(ft_strchr(tokens[i_tok].value, '<'));
	if (!dest)
		return (error_tok(*redir,
				"syntax error near unexpected token", "newline"));
	redir_t = redir_type(tokens[i_tok].value);
	if (!*redir)
	{
		if (cmd < 0)
			*redir = init_redir_wrap(dest, NULL, redir_t, close_fd);
		else
			*redir = init_redir_wrap(dest, init_cmd_node(tokens[cmd].value),
					redir_t, close_fd);
	}
	else
		make_child_for_prev(redir, dest, redir_t, close_fd);
	return (0);
}
