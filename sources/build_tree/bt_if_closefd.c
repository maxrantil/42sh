/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_if_closefd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:39:22 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/20 10:48:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_treenode	*init_closefd(int close_fd, t_treenode *cmd)
{
	t_treenode	*closefd;

	closefd = ft_memalloc(sizeof(*closefd));
	closefd->type = CLOSEFD;
	(((t_closefd *)closefd)->type) = CLOSEFD;
	(((t_closefd *)closefd)->close_fd) = close_fd;
	(((t_closefd *)closefd)->cmd) = cmd;
	return (closefd);
}

static void	make_child_for_prev(t_treenode **redir, int close_fd)
{
	if ((*redir)->type == REDIR)
		((t_redir *)(*redir))->cmd = init_closefd(close_fd,
				(((t_redir *)(*redir))->cmd));
	if ((*redir)->type == CLOSEFD)
		((t_closefd *)(*redir))->cmd = init_closefd(close_fd,
				(((t_closefd *)(*redir))->cmd));
	if ((*redir)->type == AGGREGATION)
		((t_aggregate *)(*redir))->cmd = init_closefd(close_fd,
				(((t_aggregate *)(*redir))->cmd));
	traverse_node(redir);
}

int	if_closefd(t_token *tokens, t_treenode **redir, int i_tok, int cmd)
{
	int			close_fd;

	close_fd = 0;
	close_fd = get_close_fd(tokens[i_tok].value);
	if (close_fd < 0 && ft_strchr(tokens[i_tok].value, '>'))
		close_fd = 1;
	else if (close_fd < 0 && ft_strchr(tokens[i_tok].value, '<'))
		close_fd = 0;
	if (!*redir)
	{
		if (cmd < 0)
			*redir = init_closefd(close_fd, NULL);
		else
			*redir = init_closefd(close_fd, init_cmd_node(tokens[cmd].value));
	}
	else
		make_child_for_prev(redir, close_fd);
	return (0);
}
