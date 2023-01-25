/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_combine_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:45:48 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/12 14:34:18 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*ft_trim_str_join_words(char **s1, char **s2)
{
	char	*head;
	char	*tail;
	char	*res;

	if (!*s1 || !*s2)
		return (NULL);
	head = ft_strtrim(*s1);
	ft_strdel(&head);
	head = ft_strjoin(*s1, " ");
	tail = ft_strtrim(*s2);
	res = ft_strjoin(head, tail);
	ft_strdel(&head);
	ft_strdel(&tail);
	ft_strdel(s1);
	ft_strdel(s2);
	return (res);
}

/*	Combine all word tokens. So that: ls >file -l
	becomes: ls -l >file */
void	combine_words(t_token *tokens)
{
	int		i_tok;
	int		first_word;

	i_tok = 0;
	first_word = -1;
	if (!tokens)
		return ;
	while (tokens[i_tok].value && tokens[i_tok].token != PIPE
		&& !is_logicalop(tokens[i_tok].token)
		&& !is_semicolon_or_ampersand(tokens[i_tok].token))
	{
		if (first_word < 0 && tokens[i_tok].token == WORD)
			first_word = i_tok;
		if (first_word >= 0 && first_word != i_tok
			&& tokens[i_tok].token == WORD)
		{
			tokens[first_word].value
				= ft_trim_str_join_words(&tokens[first_word].value,
					&tokens[i_tok].value);
			tokens[i_tok].token = SKIP_TOK;
		}
		++i_tok;
	}
}
