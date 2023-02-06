/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_build_and_execute_new_tree.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
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

static char	*if_heredoc(t_shell *sh, t_fc *fc)
{
	char	*new_cl;

	sh->term->fc_flag = true;
	new_cl = ft_strtrim(fc->ret_cmd);
	if (ft_heredoc_handling2(new_cl))
		remove_heredoc(new_cl);
	return (new_cl);
}

void	fc_build_and_execute_new_tree(t_shell *sh, t_fc *fc)
{
	char		*new_cl;
	t_treenode	*head;
	t_token		*tokens;

	new_cl = if_heredoc(sh, fc);
	tokens = NULL;
	tokens = chop_line(new_cl, tokens, 1);
	head = build_tree(&tokens);
	if (head && ((t_semicolon *)head)->left)
		exec_tree(head, &sh->env, sh->terminal, sh);
	free_node(head);
	free_tokens(&tokens);
	fc_free(fc);
}
