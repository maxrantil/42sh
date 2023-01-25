/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_error_after_tokenizing.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:26:19 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/19 15:31:02 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	op(int token)
{
	return (token == PIPE || token == SEMICOLON);
}

int	validate_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token)
	{
		if (tokens[i + 1].token && op(tokens[i].token)
			&& (op(tokens[i + 1].token)))
		{
			ft_err_print(NULL, "syntax error near unexpected token",
				tokens[i + 1].value, 1);
			return (1);
		}
		++i;
	}
	return (0);
}
