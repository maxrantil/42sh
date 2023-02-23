/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_build_and_execute_new_tree.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:52:49 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/23 15:05:14 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	ft_heredoc_handling2(char *str)
{
	ssize_t	count;
	ssize_t	start;

	count = 0;
	start = -1;
	while (str[++start] && count <= 2)
	{
		if (str[start] == '<')
			count++;
		else if (str[start] != '<' && count == 2)
			break ;
		else
			count = 0;
	}
	if (count == 2)
		return (1);
	else
		return (0);
}

static	void	remove_heredoc(char *str)
{
	char	*tmp;

	tmp = ft_strchr(str, '<');
	while (tmp)
	{
		ft_memmove(tmp, tmp + 1, ft_strlen(tmp));
		tmp = ft_strchr(str, '<');
	}
}

static void	if_heredoc(t_shell *sh, t_fc *fc)
{
	char	*new_cl;

	sh->term->fc_flag = true;
	new_cl = ft_strtrim(fc->ret_cmd);
	ft_strdel(&fc->ret_cmd);
	if (new_cl)
	{
		fc->ret_cmd = new_cl;
		if (ft_heredoc_handling2(fc->ret_cmd))
			remove_heredoc(fc->ret_cmd);
	}
	else
	{
		ft_putchar('\n');
		ft_history_add_command(sh->term, "-");
	}
}

void	fc_build_and_execute_new_tree(t_shell *sh, t_fc *fc)
{
	t_treenode	*head;
	t_token		*tokens;

	if_heredoc(sh, fc);
	tokens = NULL;
	if (fc->ret_cmd)
	{
		tokens = chop_line(fc->ret_cmd, tokens, 1);
		head = build_tree(&tokens);
		if (head && ((t_semicolon *)head)->left)
			exec_tree(head, &sh->env, sh->terminal, sh);
		free_node(head);
		free_tokens(&tokens);
	}
	fc_free(fc);
}
