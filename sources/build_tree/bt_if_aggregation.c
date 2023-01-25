/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_if_aggregation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:18:53 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/19 16:13:41 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_treenode	*init_aggregation_node(int close_fd, char *dest, t_treenode *cmd)
{
	t_treenode	*res;

	res = ft_memalloc(sizeof(*res));
	res->type = AGGREGATION;
	((t_aggregate *)res)->type = AGGREGATION;
	((t_aggregate *)res)->close_fd = close_fd;
	((t_aggregate *)res)->dest = dest;
	((t_aggregate *)res)->cmd = cmd;
	return (res);
}

static void	make_child_for_prev(t_treenode **redir,
		char *dest, int close_fd)
{
	if ((*redir)->type == REDIR)
		((t_redir *)(*redir))->cmd = init_aggregation_node(close_fd,
				dest, (((t_redir *)(*redir))->cmd));
	if ((*redir)->type == CLOSEFD)
		((t_closefd *)(*redir))->cmd = init_aggregation_node(close_fd,
				dest, (((t_closefd *)(*redir))->cmd));
	if ((*redir)->type == AGGREGATION)
		((t_aggregate *)(*redir))->cmd = init_aggregation_node(close_fd,
				dest, (((t_aggregate *)(*redir))->cmd));
	traverse_node(redir);
}

static int	check_dest(char **dest, int close_fd, char *token_val)
{
	char	c;

	*dest = get_file(ft_strchr(token_val, '>'));
	if (!*dest)
		*dest = get_file(ft_strchr(token_val, '<'));
	if (!*dest)
		return (-1);
	c = **dest;
	if (close_fd == 1 && (ft_isalnum(c) || c == '/' || c == '$' || c == '~'))
		return (0);
	else if (close_fd == 1)
		return (-1);
	if (close_fd != 1 && ft_isdigit(c))
		return (0);
	return (1);
}

static int	handle_error(int ret,
		t_treenode *redir, char **dest)
{
	if (ret == -1)
	{
		ft_strdel(dest);
		return (error_tok(redir,
				"syntax error near unexpected token", "newline"));
	}
	if (ret == 1 && ft_err_print(NULL, *dest, "ambiguous redirect", 2))
	{
		ft_strdel(dest);
		return (error_tok(redir, NULL, NULL));
	}
	return (0);
}

int	if_aggregation(t_token *tokens, t_treenode **redir, int i_tok, int cmd)
{
	char	*dest;
	int		close_fd;
	int		ret;

	close_fd = get_close_fd(tokens[i_tok].value);
	if (close_fd < 0 && ft_strchr(tokens[i_tok].value, '>'))
		close_fd = 1;
	else if (close_fd < 0 && ft_strchr(tokens[i_tok].value, '<'))
		close_fd = 0;
	ret = check_dest(&dest, close_fd, tokens[i_tok].value);
	if (handle_error(ret, *redir, &dest))
		return (1);
	if (!*redir)
	{
		if (cmd < 0)
			*redir = init_aggregation_node(close_fd, dest, NULL);
		else
			*redir = init_aggregation_node(close_fd,
					dest, init_cmd_node(tokens[cmd].value));
	}
	else
		make_child_for_prev(redir, dest, close_fd);
	return (0);
}
