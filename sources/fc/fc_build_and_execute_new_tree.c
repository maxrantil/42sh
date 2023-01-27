/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_build_and_execute_new_tree.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:52:49 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/27 19:39:42 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	ft_heredoc_handling2(t_term *t, char *str)
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
		t->heredoc = 1;
	else
		t->heredoc = 0;
}

static void	delim_fetch_error2(t_term *t, char *ptr, char *str)
{
	if (*ptr && ft_isseparator(*ptr))
	{
		ft_putstr_fd("\n42sh: syntax error near unexpected token `", 2);
		write(2, ptr, 1);
		ft_putstr_fd("'", 2);
	}
	else
		ft_putstr_fd("\n42sh: syntax error near unexpected token `newline'", 2);
	// ft_strclr(t->inp);
	ft_strdel(&str);
	t->heredoc = 0;
}

static char	*strdelim2(char *str)
{
	char	*ptr;
	int		delim_qty;

	ptr = str;
	delim_qty = 0;
	while (*ptr)
	{
		if (*ptr == '<')
			delim_qty++;
		if (delim_qty == 2)
			return (ptr + 1);
		ptr++;
	}
	return (ptr);
}

/*
 * It fetches the delimiter
 * for a heredoc
 *
 * @param t the term structure
 */
static int	ft_delim_fetch2(t_term *t, char *str)
{
	char	*ptr;
	char	*end_q;

	if (t->heredoc && !t->delim)
	{
		ptr = strdelim2(str);
		while (*ptr && ft_isspace(*ptr))
			ptr++;
		if (*ptr && !ft_isseparator(*ptr))
		{
			end_q = ptr;
			while (*end_q && !ft_isspace(*end_q))
				end_q++;
			t->delim = ft_strsub(ptr, 0, (size_t)(end_q - ptr));
		}
		else
		{
			delim_fetch_error2(t, ptr, str);
			return (1);
		}
	}
	return (0);
}

static void	ft_flag_reset(t_term *t, char *str)
{
	ssize_t	i;

	i = -1;
	t->q_qty = 0;
	t->quote = 0;
	t->heredoc = 0;
	if (t->delim)
		ft_strdel(&t->delim);
	while (str[++i])
	{
		if ((str[i] == D_QUO || str[i] == S_QUO) && !t->heredoc)
		{
			if (!special_char_check(str, t->index - 1, '\\'))
				ft_quote_handling(t, str[i]);
		}
		if (str[i] == '<' && !t->quote)
			ft_heredoc_handling2(t, str);
	}
}

void	fc_build_and_execute_new_tree(t_shell *sh, t_fc *fc)
{
	char		*new;
	t_treenode	*head;
	t_token		*tokens;

	sh->term->fc_flag = true;
	new = ft_strtrim(fc->ret_cmd);
	ft_printf("new = %s\n", new);
	ft_flag_reset(sh->term, new);
	if (sh->term->heredoc)
		ft_delim_fetch2(sh->term, new);
	if (new)
		new = ft_heredoc(sh->term, new);
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
