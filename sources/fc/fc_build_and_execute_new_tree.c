/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_build_and_execute_new_tree.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:52:49 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 19:49:45 by mrantil          ###   ########.fr       */
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

void	fc_build_and_execute_new_tree(t_shell *sh, t_fc *fc)
{
	char		*new;
	t_treenode	*head;
	t_token		*tokens;

	sh->term->fc_flag = true;
	new = ft_strtrim(fc->ret_cmd);
	if (ft_heredoc_handling2(new))
		remove_heredoc(new);
	ft_freeda((void ***)&fc->filename, calc_chptr(fc->filename));
	tokens = NULL;
	tokens = chop_line(new, tokens, 1);
	head = build_tree(&tokens);
	if (head && ((t_semicolon *)head)->left)
		exec_tree(head, &sh->env, sh->terminal, sh);
	free_node(head);
	free_tokens(&tokens);
	ft_strdel(&fc->ret_cmd);
}
