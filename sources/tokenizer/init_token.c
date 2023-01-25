/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:38:01 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/06 17:36:54 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	set_token_values(t_token *token, int token_id, char *value)
{
	token->token = token_id;
	if (value)
		token->value = value;
}

void	init_token(char *c, t_token *token, char *line, int cur)
{
	if (line[cur] == '|' && line[cur + 1] == '|')
		set_token_values(token, LOGICAL_OR, c);
	else if (line[cur] == '&' && line[cur + 1] == '&')
		set_token_values(token, LOGICAL_AND, c);
	else if (line[cur] == '&')
		set_token_values(token, AMPERSAND, c);
	else if (*c == '|')
		set_token_values(token, PIPE, c);
	else if (line[cur] == '>' || line[cur] == '<')
	{
		if (line[cur + 1] && line[cur + 2] && line[cur + 1] == '&'
			&& line[cur + 2] == '-')
			set_token_values(token, CLOSEFD, c);
		else if (line[cur + 1] == '&')
			set_token_values(token, AGGREGATION, c);
		else
			set_token_values(token, REDIR, c);
	}
	else if (*c == ';')
		set_token_values(token, SEMICOLON, c);
	else
		set_token_values(token, WORD, c);
}
